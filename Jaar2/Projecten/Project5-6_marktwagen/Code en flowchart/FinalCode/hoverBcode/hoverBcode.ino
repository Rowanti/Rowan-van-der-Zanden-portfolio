#define HOVER_SERIAL_BAUD 115200  // [-] Baud rate for HoverSerial (used to communicate with the hoverboard)
#define SERIAL_BAUD 115200        // [-] Baud rate for built-in Serial (used for the Serial Monitor)
#define START_FRAME 0xABCD        // [-] Start frame definition for reliable serial communication
#define TIME_SEND 100             // [ms] Sending time interval
#define SPEED_MAX_TEST 300        // [-] Maximum speed for testing
#define SPEED_STEP 20             // [-] Speed step

#include <Wire.h>
#include <DFRobot_QMC5883.h>


DFRobot_QMC5883 compass;
#include <SoftwareSerial.h>
SoftwareSerial HoverSerial(2, 3);  // RX, TX

uint8_t idx = 0;         // Index for new data pointer
uint16_t bufStartFrame;  // Buffer Start Frame
byte *p;                 // Pointer declaration for the new received data
byte incomingByte;
byte incomingBytePrev;

typedef struct {
  uint16_t start;
  int16_t steer;
  int16_t speeds;
  uint16_t checksum;
} SerialCommand;
SerialCommand Command;

typedef struct {
  uint16_t start;
  int16_t cmd1;
  int16_t cmd2;
  int16_t speedR_meas;
  int16_t speedL_meas;
  int16_t batVoltage;
  int16_t boardTemp;
  uint16_t cmdLed;
  uint16_t checksum;
} SerialFeedback;
SerialFeedback Feedback;
SerialFeedback NewFeedback;

byte echoPins[] = { 6 };  // first 3 are facing the front
byte trigPins[] = { 7 };

byte echoSide[] = { 4, 8 };  // facing the sides
byte trigSide[] = { 5, 9 };
size_t n = sizeof(echoPins) / sizeof(echoPins[0]);
size_t m = sizeof(echoSide) / sizeof(echoSide[0]);

unsigned long lastCheck;
unsigned long timer = millis();

void setup() {
  // put your setup code here, to run once:
  Serial.begin(SERIAL_BAUD);
  Serial.println("Hoverboard Serial v1.0");
  HoverSerial.begin(HOVER_SERIAL_BAUD);
  pinMode(LED_BUILTIN, OUTPUT);
  Send(60, 0);
  for (byte i = 0; i < n; i++) {
    pinMode(echoPins[i], INPUT);
  }
  for (byte i = 0; i < n; i++) {
    pinMode(trigPins[i], OUTPUT);
  }
  for (byte i = 0; i < m; i++) {
    pinMode(echoSide[i], INPUT);
  }
  for (byte i = 0; i < m; i++) {
    pinMode(trigSide[i], OUTPUT);
  }
  while (!compass.begin()) {
    Serial.println("Could not find a valid QMC5883 sensor, check wiring!");
    delay(500);
  }
  if (compass.isHMC()) {
    Serial.println("Initialize HMC5883");
    compass.setRange(HMC5883L_RANGE_1_3GA);
    compass.setMeasurementMode(HMC5883L_CONTINOUS);
    compass.setDataRate(HMC5883L_DATARATE_15HZ);
    compass.setSamples(HMC5883L_SAMPLES_8);
  } else if (compass.isQMC()) {
    Serial.println("Initialize QMC5883");
    compass.setRange(QMC5883_RANGE_2GA);
    compass.setMeasurementMode(QMC5883_CONTINOUS);
    compass.setDataRate(QMC5883_DATARATE_50HZ);
    compass.setSamples(QMC5883_SAMPLES_8);
  }
  while (detect() != 0) {
    drive(4);
    delay(100);
  }
}
void Send(int16_t uSteer, int16_t uSpeed) {
  // Create command
  Command.start = (uint16_t)START_FRAME;
  Command.steer = (int16_t)uSteer;
  Command.speeds = (int16_t)uSpeed;
  Command.checksum = (uint16_t)(Command.start ^ Command.steer ^ Command.speeds);

  // Write to Serial
  HoverSerial.write((uint8_t *)&Command, sizeof(Command));
}
void Receive() {
  // Check for new data availability in the Serial buffer
  if (HoverSerial.available()) {
    incomingByte = HoverSerial.read();                                   // Read the incoming byte
    bufStartFrame = ((uint16_t)(incomingByte) << 8) | incomingBytePrev;  // Construct the start frame
  } else {
    return;
  }

// If DEBUG_RX is defined print all incoming bytes
#ifdef DEBUG_RX
  Serial.print(incomingByte);
  return;
#endif

  // Copy received data
  if (bufStartFrame == START_FRAME) {  // Initialize if new data is detected
    p = (byte *)&NewFeedback;
    *p++ = incomingBytePrev;
    *p++ = incomingByte;
    idx = 2;
  } else if (idx >= 2 && idx < sizeof(SerialFeedback)) {  // Save the new received data
    *p++ = incomingByte;
    idx++;
  }

  // Check if we reached the end of the package
  if (idx == sizeof(SerialFeedback)) {
    uint16_t checksum;
    checksum = (uint16_t)(NewFeedback.start ^ NewFeedback.cmd1 ^ NewFeedback.cmd2 ^ NewFeedback.speedR_meas ^ NewFeedback.speedL_meas
                          ^ NewFeedback.batVoltage ^ NewFeedback.boardTemp ^ NewFeedback.cmdLed);

    // Check validity of the new data
    if (NewFeedback.start == START_FRAME && checksum == NewFeedback.checksum) {
      // Copy the new data
      memcpy(&Feedback, &NewFeedback, sizeof(SerialFeedback));

      // Print data to built-in Serial
      Serial.print("1: ");
      Serial.print(Feedback.cmd1);
      Serial.print(" 2: ");
      Serial.print(Feedback.cmd2);
      Serial.print(" 3: ");
      Serial.print(Feedback.speedR_meas);
      Serial.print(" 4: ");
      Serial.print(Feedback.speedL_meas);
      Serial.print(" 5: ");
      Serial.print(Feedback.batVoltage);
      Serial.print(" 6: ");
      Serial.print(Feedback.boardTemp);
      Serial.print(" 7: ");
      Serial.println(Feedback.cmdLed);
    } else {
      Serial.println("Non-valid data skipped");
    }
    idx = 0;  // Reset the index (it prevents to enter in this if condition in the next cycle)
  }
  // Update previous states
  incomingBytePrev = incomingByte;
}

float measure(int trigPin, int echoPin) {
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
  return distance;
}
int detect() {
  int sensorDetect = 0;
  for (byte i = 0; i < n; i++) {
    if (measure(trigPins[i], echoPins[i]) < 60) {
      sensorDetect = 2;
    }
  }
  if (sensorDetect != 0) {
    int closest = 0;
    for (byte i = 0; i < m; i++) {
      if (measure(trigSide[closest], echoSide[closest]) >= measure(trigSide[i], echoSide[i])) {
        closest = i;
      }
    }
    if (closest < m / 2) {
      sensorDetect = 1;
    } else {
      sensorDetect = 3;
    }
  }
  if (sensorDetect != 0) {
    Serial.print("middle: ");
    Serial.println(sensorDetect);
    return sensorDetect;
  }
  for (byte i = 0; i < m; i++) {
    int closest = 0;
    if (measure(trigSide[i], echoSide[i]) < 35) {
      if (measure(trigSide[closest], echoSide[closest]) >= measure(trigSide[i], echoSide[i])) {
        if (i < m / 2) {
          sensorDetect = 1;
        } else {
          sensorDetect = 3;
        }
      }
    }
  }
  Serial.print("other: ");
  Serial.println(sensorDetect);
  return sensorDetect;
}
void drive(int detect) {
  switch (detect) {
    case 0:
      Send(0, 50);
      // Serial.println("GOOOO");
      break;
    case 1:
      lastCheck = millis();
      // Serial.println("left");
      Send(-60, 0);
      break;
    case 3:
      lastCheck = millis();
      // Serial.println("right");
      Send(60, 0);
      break;
    default:
      // Serial.println("idk");
      Send(0, 0);
      break;
  }
}
void compareDegrees(float self, float other) {
  float tolerance = 5.0;
  float selfDegrees = self;
  while (other + tolerance < selfDegrees || other - tolerance > selfDegrees) {
    selfDegrees = readDegrees();
    Serial.println("AAAAAAAAAAAAAAAH");
    if (other < selfDegrees) {
      Send(-60, 0);
    } else {
      Send(60, 0);
    }
    delay(30);
  }
}

//degrees to beacon
int getDegrees() {
  // Serial.readBytes(degrees,1);
  // return degrees;
  return 150;
}
//self pointing degrees
float readDegrees() {
  Vector norm = compass.readNormalize();

  // Calculate heading
  float heading = atan2(norm.YAxis, norm.XAxis);

  // Set declination angle on your location and fix heading
  // You can find your declination on: http://magnetic-declination.com/
  // (+) Positive or (-) for negative
  // For Bytom / Poland declination angle is 4'26E (positive)
  // Formula: (deg + (min / 60.0)) / (180 / M_PI);
  float declinationAngle = (4.0 + (26.0 / 60.0)) / (180 / PI);
  heading += declinationAngle;

  // Correct for heading < 0deg and heading > 360deg
  if (heading < 0) {
    heading += 2 * PI;
  }
  if (heading > 2 * PI) {
    heading -= 2 * PI;
  }

  // Convert to degrees
  float headingDegrees = heading * 180 / M_PI;

  // Output
  // Serial.print(" Heading = ");
  // Serial.print(heading);
  Serial.print(" Degress = ");
  Serial.print(headingDegrees);
  Serial.println();
  return headingDegrees;
}

float otherDegrees;
float selfDegrees;
float previous;
void loop() {
  timer = millis();
  // otherDegrees = getDegrees();
  otherDegrees = 340.0;
  selfDegrees = readDegrees();
  if (timer - lastCheck >= 5000) {
    lastCheck = millis();
    previous = otherDegrees;
    compareDegrees(selfDegrees, otherDegrees);
  } else {
    // previous -= 100;
    drive(detect());
  }
  // drive(detect());
  Receive();
  delay(100);
}
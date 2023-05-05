#include<Wire.h>
#include<arduinio.h>
#define I2C_ADDRESS 1

int DS1_pin = 4;
int STCP1_pin = 3;
int SHCP1_pin = 2 ;
int REED_PIN = 5;
int LED_ROOD = 6;
int LED_GROEN = 7;
const int BUTTON = 8;
const int LED_BUTTON = 9;
int BUTTONstate = 0;
const int BUTTON2 = 10;
const int LED_BUTTON2 = 11;
int BUTTON2state = 0;
int verdiepingStatus;

int digits [10][8] {
  {0, 1, 1, 1, 1, 1, 1, 0}, // digit 0
  {0, 0, 1, 1, 0, 0, 0, 0}, // digit 1
  {0, 1, 1, 0, 1, 1, 0, 1}, // digit 2
  {0, 1, 1, 1, 1, 0, 0, 1}, // digit 3
  {0, 0, 1, 1, 0, 0, 1, 1}, // digit 4
  {0, 1, 0, 1, 1, 0, 1, 1}, // digit 5
  {0, 1, 0, 1, 1, 1, 1, 1}, // digit 6
  {0, 1, 1, 1, 0, 0, 0, 0}, // digit 7
  {0, 1, 1, 1, 1, 1, 1, 1}, // digit 8
  {0, 1, 1, 1, 1, 0, 1, 1} // digit 9
};

void display_digit(int d) {
  if (digits[d][0] == 1) digitalWrite(7, LOW); else digitalWrite(7, HIGH); //A
  if (digits[d][1] == 1) digitalWrite(6, LOW); else digitalWrite(6, HIGH); //B
  if (digits[d][2] == 1) digitalWrite(4, LOW); else digitalWrite(4, HIGH); //C
  if (digits[d][3] == 1) digitalWrite(2, LOW); else digitalWrite(2, HIGH); //D
  if (digits[d][4] == 1) digitalWrite(1, LOW); else digitalWrite(1, HIGH); //E
  if (digits[d][5] == 1) digitalWrite(9, LOW); else digitalWrite(9, HIGH); //F
  if (digits[d][6] == 1) digitalWrite(10, LOW); else digitalWrite(10, HIGH); //G
}

void DisplayDigit(int Digit)
{
  digitalWrite(STCP1_pin, LOW);
  for (int i = 7; i >= 0; i--)
  {
    digitalWrite(SHCP1_pin, LOW);
    if (digits[Digit][i] == 0) digitalWrite(DS1_pin, LOW);
    if (digits[Digit][i] == 1) digitalWrite(DS1_pin, HIGH);
    digitalWrite(SHCP1_pin, HIGH);
  }
  digitalWrite(STCP1_pin, HIGH);
}
void requestEvent();
void receiveEvent();

void setup() {
  Wire.begin(I2C_ADDRESS);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("test");
  pinMode(DS1_pin, OUTPUT);
  pinMode(STCP1_pin, OUTPUT);
  pinMode(SHCP1_pin, OUTPUT);
  pinMode(REED_PIN, INPUT);
  pinMode(LED_GROEN, OUTPUT);
  pinMode(LED_ROOD, OUTPUT);
  pinMode(BUTTON, INPUT);
  pinMode(LED_BUTTON, OUTPUT);
  pinMode(BUTTON2, INPUT);
}

void loop() {
  BUTTONstate = digitalRead(BUTTON);
  BUTTON2state = digitalRead(BUTTON2);
  static unsigned long startTime = millis();
  int REEDState = digitalRead(REED_PIN);
  Serial.println(REEDState);
  Serial.println(BUTTONstate);
  Serial.println(BUTTON2state);
  Serial.println("__________________________________________________________________________");
  if (REEDState == LOW && BUTTONstate == HIGH && BUTTON2state == HIGH) {
    int i = 1;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON, HIGH);
    digitalWrite(LED_BUTTON2, HIGH);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_GROEN, HIGH);
      digitalWrite(LED_ROOD, LOW);
    }
  }
  if (REEDState == HIGH && BUTTONstate == HIGH && BUTTON2state == HIGH) {
    int i = verdiepingStatus;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON, HIGH);
    digitalWrite(LED_BUTTON2, HIGH);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_GROEN, LOW);
      digitalWrite(LED_ROOD, HIGH);
    }
  }
  if (REEDState == LOW && BUTTONstate == LOW && BUTTON2state == HIGH) {
    int i = 1;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON2, HIGH);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_GROEN, HIGH);
      digitalWrite(LED_ROOD, LOW);
      digitalWrite(LED_BUTTON, LOW);
    }
  }
  if (REEDState == HIGH && BUTTON2state == HIGH) {
    int i = verdiepingStatus;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON2, HIGH);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_GROEN, LOW);
      digitalWrite(LED_ROOD, HIGH);
    }
  }
  //.......................................................................................................
  if (REEDState == LOW && BUTTONstate == HIGH && BUTTON2state == LOW) {
    int i = 1;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON, HIGH);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_GROEN, HIGH);
      digitalWrite(LED_ROOD, LOW);
      digitalWrite(LED_BUTTON2, LOW);
    }
  }
  if (REEDState == HIGH && BUTTONstate == HIGH) {
    int i = verdiepingStatus;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON, HIGH);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_GROEN, LOW);
      digitalWrite(LED_ROOD, HIGH);
    }
  }
  if (REEDState == LOW && BUTTONstate == LOW && BUTTON2state == LOW ) {
    int i = 1;
    DisplayDigit(i);
    digitalWrite(LED_BUTTON, LOW);
    digitalWrite(LED_BUTTON2, LOW);
    if (millis() - startTime >= 2000) {
      digitalWrite(LED_ROOD, LOW);
      digitalWrite(LED_GROEN, HIGH);
    }
  }
  else {
    int i = verdiepingStatus;
    DisplayDigit(i);
    digitalWrite(LED_GROEN, LOW);
    digitalWrite(LED_ROOD, HIGH);
    startTime = millis();
  }
}

void requestEvent() {
  BUTTONstate = digitalRead(BUTTON);
  BUTTON2state = digitalRead(BUTTON2);
  int REEDState = digitalRead(REED_PIN);
  int REED;
  if (REEDState == 0) {
    REED = 1;
  }
  if (REEDState == 1) {
    REED = 0;
  }
  byte data = 0;
  data += 1;
  data = data << 1;
  data += REED;
  data = data << 1;
  data += BUTTONstate;
  data = data << 1;
  data += BUTTON2state;
  Wire.write(data);
}

void receiveEvent() {
  verdiepingStatus = Wire.read();
  Serial.println(verdiepingStatus);
}

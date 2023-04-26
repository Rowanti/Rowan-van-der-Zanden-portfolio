#include <Arduino.h>
#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
  int a;
  int b;
  int c;
  int d;
  int e;
} struct_message;
struct_message myData;


#define motorpinL1 17 //motorlinks
#define motorpinL2 5
#define motorpinR1 27 //motorrechts
#define motorpinR2 14
int EN1 = 25;
int EN2 = 26;
#define IRL 36 //IRlinks
#define IRR 35 //IRrechts

#define LED 13 //led als test voor de REED
#define REED 12 //REED

const int echoPinOnder = 4; //echo pin US
const int trigPinOnder = 16; //trig pin US
long durationOnder; //duration US
int distanceOnder; // afstand

const int echoPinLinks = 32; //echo pin US
const int trigPinLinks = 33; //trig pin US
long durationLinks; //duration US
int distanceLinks; // afstand


const int echoPinRechts = 18; //echo pin US
const int trigPinRechts = 19; //trig pin US
long durationRechts; //duration US
int distanceRechts; // afstand

static unsigned long startTime;

//status IR
int IRlinks;
int IRrechts;
int REEDstatus;
int maxIR = 750; //maximale waarde dat geld om iets waar te nemen
int maxUS = 50;
int maxUSO = 8;
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 230;
const int freq2 = 30000;
const int pwmChannel2 = 0;
const int resolution2 = 8;
int dutyCycle2 = 230;




void linksVoor();
void linksAchter();
void rechtsVoor();
void rechtsAchter();
void voor();
void achter();
void ontwijken();
void bijsturen();
void IRsensor();
void USlinks();
void USrechts();
void USonder();
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("Bytes received!");
}

void linksVoor() {
  digitalWrite(motorpinL1, LOW);
  digitalWrite(motorpinL2, LOW);
  digitalWrite(motorpinR1, LOW);
  digitalWrite(motorpinR2, HIGH);
  Serial.println("naar links");
}
void linksAchter() {
  digitalWrite(motorpinL1, LOW);
  digitalWrite(motorpinL2, HIGH);
  digitalWrite(motorpinR1, LOW);
  digitalWrite(motorpinR2, LOW);
  Serial.println("naar links");
}
void rechtsVoor() {
  digitalWrite(motorpinL1, HIGH);
  digitalWrite(motorpinL2, LOW);
  digitalWrite(motorpinR1, LOW);
  digitalWrite(motorpinR2, LOW);
  Serial.println("kies rechts");
}
void rechtsAchter() {
  digitalWrite(motorpinL1, LOW);
  digitalWrite(motorpinL2, LOW);
  digitalWrite(motorpinR1, HIGH);
  digitalWrite(motorpinR2, LOW);
  Serial.println("naar rechts");
}
void voor() {
  digitalWrite(motorpinL1, HIGH);
  digitalWrite(motorpinL2, LOW);
  digitalWrite(motorpinR1, LOW);
  digitalWrite(motorpinR2, HIGH);
  Serial.println("naar voren");
}
void achter() {
  digitalWrite(motorpinL1, LOW);
  digitalWrite(motorpinL2, HIGH);
  digitalWrite(motorpinR1, HIGH);
  digitalWrite(motorpinR2, LOW);
  Serial.println("naar achter");
}

void ontwijken() { //De motor een bepaalde kant op laten draaien afhankelijk van de US waarde
  if (distanceLinks <= maxUS && distanceRechts > maxUS && distanceOnder <= maxUSO) {
    rechtsVoor();
  }
  else if (distanceLinks > maxUS && distanceRechts <= maxUS && distanceOnder <= maxUSO) {
    linksVoor();
  }
  else if (distanceLinks <= maxUS && distanceRechts <= maxUS && distanceOnder <= maxUSO) {
    if (distanceLinks < distanceRechts) {
      rechtsVoor();
    }
    else {
      linksVoor();
    }
  }
}
void bijsturen() {
  if (IRlinks > maxIR && IRrechts <= maxIR) {
    rechtsAchter();
  }
  else if (IRlinks <= maxIR && IRrechts > maxIR) {
    linksAchter();
  }
  else if (IRlinks > maxIR && IRrechts > maxIR) {
    linksAchter();
  }
}
void IRsensor() {
  IRrechts = analogRead(IRR);
  IRlinks = analogRead(IRL);
  startTime = millis();
  Serial.println("Test");
  Serial.println(IRrechts);
  Serial.println(IRlinks);
}

void USlinks() {
  //________ultrasoon Links_________________________
  digitalWrite(trigPinLinks, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinLinks, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinLinks, LOW);
  durationLinks = pulseIn(echoPinLinks, HIGH);
  distanceLinks = durationLinks * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distanceLinks);
  Serial.println(" cm");
  //_________________________________________________
}
void USrechts() {
  //________ultrasoon Rechts_________________________
  digitalWrite(trigPinRechts, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinRechts, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinRechts, LOW);
  durationRechts = pulseIn(echoPinRechts, HIGH);
  distanceRechts = durationRechts * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distanceRechts);
  Serial.println(" cm");
  //_________________________________________________
  // USonder();
}
void USonder() {
  //________ultrasoon Onder_________________________
  digitalWrite(trigPinOnder, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPinOnder, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinOnder, LOW);
  durationOnder = pulseIn(echoPinOnder, HIGH);
  distanceOnder = durationOnder * 0.034 / 2;
  Serial.print("Distance: ");
  Serial.print(distanceOnder);
  Serial.println(" cm");
  //_________________________________________________
}

void setup() {
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  pinMode(motorpinL1, OUTPUT);
  pinMode(motorpinL2, OUTPUT);
  pinMode(motorpinR1, OUTPUT);
  pinMode(motorpinR2, OUTPUT);
  pinMode(EN1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(IRL, INPUT);
  pinMode(IRR, INPUT);

  pinMode(REED, INPUT);
  pinMode(LED, OUTPUT);

  pinMode(trigPinLinks, OUTPUT);
  pinMode(echoPinLinks, INPUT);
  pinMode(trigPinRechts, OUTPUT);
  pinMode(echoPinRechts, INPUT);
  pinMode(trigPinOnder, OUTPUT);
  pinMode(echoPinOnder, INPUT);
  ledcSetup(pwmChannel, freq, resolution);
  ledcSetup(pwmChannel2, freq2, resolution2);
  ledcAttachPin(EN1, pwmChannel);
  ledcAttachPin(EN2, pwmChannel2);
  Serial.begin(9600);
}

void loop() {
  REEDstatus = digitalRead(REED);
  if (REEDstatus == LOW) {
  digitalWrite(LED, HIGH);
  }
  if (myData.a == 0) {
    ledcWrite(pwmChannel, dutyCycle);
    ledcWrite(pwmChannel2, dutyCycle2);
    // REEDstatus = digitalRead(REED);
    USonder();
    if (millis() - startTime > 100) {
      IRsensor();
      USlinks();
      USrechts();
      Serial.println("___________________________");
      Serial.println(distanceLinks);
      Serial.println(distanceRechts);
      Serial.println(distanceOnder);
      Serial.println("_________________________");
    }

    Serial.println(IRlinks);
    Serial.println(IRrechts);
    if (distanceOnder > maxUSO) {
      ledcWrite(pwmChannel, 255);
      ledcWrite(pwmChannel2, 255);
      rechtsAchter();
      delay(1000);
      rechtsVoor();
      delay(1000);
      rechtsAchter();
      delay(1000);
      rechtsVoor();
      delay(1000);
      rechtsAchter();
      delay(1000);
      // rechtsVoor();
      // delay(1000);
      IRsensor();
      ledcWrite(pwmChannel, dutyCycle);
      ledcWrite(pwmChannel2, dutyCycle2);
      //startTime = millis();
    }
    else if (IRlinks > maxIR || IRrechts > maxIR) {
      bijsturen();
    }
    else if (distanceLinks < maxUS || distanceRechts < maxUS /*|| distanceOnder > maxUSO*/) {
      ontwijken();
    }
    else {
      voor();
    }
  } else {
      ledcWrite(pwmChannel, 255);
      ledcWrite(pwmChannel2, 255);
    //linkerkant besturen
    if (myData.b == 1) {
      //links links knopje = linkerkant achteruit draaien
      digitalWrite(motorpinL1, LOW);
      digitalWrite(motorpinL2, HIGH);
    } else if (myData.c == 1) {
      //midden links knopje = linkerkant vooruit draaien
      digitalWrite(motorpinL1, HIGH);
      digitalWrite(motorpinL2, LOW);
    } else {
      //standaard staat de linkerkant uit
      digitalWrite(motorpinL1, LOW);
      digitalWrite(motorpinL2, LOW);
    }

    //rechterkant besturen
    if (myData.d == 1) {
      //midden rechts knopje = rehterkant achteruit draaien
      digitalWrite(motorpinR1, HIGH);
      digitalWrite(motorpinR2, LOW);
    } else if (myData.e == 1) {
      //rechts rechts knopje = rechterkant vooruit draaien
      digitalWrite(motorpinR1, LOW);
      digitalWrite(motorpinR2, HIGH);
    } else {
      //standaard staat de rechterkant uit
      digitalWrite(motorpinR1, LOW);
      digitalWrite(motorpinR2, LOW);
    }
  }
}
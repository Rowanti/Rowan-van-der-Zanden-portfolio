#include <Servo.h>  // add servo library

Servo myservo;  // create servo object to control a servo
#define sensorPower 7   //de powerline van de waterlevelsensor
#define sensorPin A0    //de inputline van de waterlevelsensor

int val;    // variable to read the value from the analog pin
int minLevel = 120;     //minimale waterlevel om de servo te bewegen
int maxLevel = 160;     //het maximale waterlevel om de servo te laten bewegen

void setup() {
  Serial.begin(9600);
  pinMode(sensorPower, OUTPUT);
  pinMode(sensorPin, INPUT);
  myservo.attach(9);  // de servo pin
  myservo.write(90);  // de servo openen om het water dat er in zit eruit te halen
  delay(1000);
}

void loop() {
  //leest een eerste waarde uit
  int level = readSensor();
  int level2;
  if (level >= minLevel) {
    delay(250);
    //leest een tweede waarde uit om te kijken of het waterlevel niet aan het stijgen is, als dit wel zo is zal de servo aangezet worden.
    int level2 = readSensor();
    if (level <= level2) {
      if (level <= 156 && level >= minLevel) {
        level = map(level, minLevel, maxLevel, 0, 180);     // de schaal maken van de waterlevelsensor met de servo
        myservo.write(level);
        delay(200);
      }
      else if (level < minLevel) {
        myservo.write(0);
      } else {
        return;
      }
    }
    else {
      return;
    }
  }
  else if (level < minLevel) {
    myservo.write(0);
    delay(250);
  }

}
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Zet de sensor aan
  delay(10);
  val = analogRead(sensorPin);
  Serial.println(val);
  digitalWrite(sensorPower, LOW);   // Zet de sensor uit
  return val;
}

#include <Wire.h>
#include <Keypad.h>

#define SLAVE_0 10
#define SLAVE_1 1
#define SLAVE_2 2
#define SLAVE_3 3
#define SLAVE_4 4


int verdieping;
int knopOproep;
char Press;
int gelijk;
char PressState = '7';
const int motorpin1 = 10;
const int motorpin2 = 11;
const byte ROWS = 4;
const byte COLS = 4;

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Wire.begin();
  Serial.begin(9600);
  pinMode(motorpin1, OUTPUT);
  pinMode(motorpin2, OUTPUT);
}

void loop() {
  char customKey = customKeypad.getKey();
  int eindverdieping;
  //Serial.print(customKey);
  if (customKey) {
    if (customKey >= '0' && customKey <= '4') {
      eindverdieping = customKey - 48;
    }
    else {
      eindverdieping = '7';
    }
  }
  Serial.print(eindverdieping);
  Serial.println("________________");
  Serial.println(knopOproep);

  if (verdieping != eindverdieping && eindverdieping <= '4' && eindverdieping <= '0') {
    if (verdieping < eindverdieping) {
      digitalWrite(motorpin1, HIGH);
      digitalWrite(motorpin2, LOW);
      Serial.println("niet gelijk up");
    }
    if (verdieping == eindverdieping) {
      eindverdieping = '7' - 48;
      digitalWrite(motorpin1, LOW);
      digitalWrite(motorpin2, LOW);
      Serial.println("niet gelijk gelijk");
    }
    if (verdieping > eindverdieping ) {
      digitalWrite(motorpin1, LOW);
      digitalWrite(motorpin2, HIGH);
      Serial.println("niet gelijk down");
    }
  }

  if (verdieping == eindverdieping && eindverdieping <= '4' && eindverdieping <= '0') {
    eindverdieping = '7';
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
    Serial.println("gelijk");
    Serial.println(eindverdieping);
  }
  if (knopOproep == verdieping && knopOproep <= 4 && knopOproep >= 0) {
    knopOproep = '7';
    digitalWrite(motorpin1, LOW);
    digitalWrite(motorpin2, LOW);
  }
  if(eindverdieping == '7'){
  if (knopOproep != verdieping && knopOproep <= 4 && knopOproep >= 0) {
    if (knopOproep < verdieping && knopOproep <= 4 && knopOproep >= 0) {
      digitalWrite(motorpin1, LOW);
      digitalWrite(motorpin2, HIGH);
      Serial.println("knop up");
    }
    if (knopOproep > verdieping && knopOproep <= 4 && knopOproep >= 0) {
      digitalWrite(motorpin1, HIGH);
      digitalWrite(motorpin2, LOW);
      Serial.println("knop down");
    }
  }
  }
  Wire.beginTransmission(SLAVE_0);
  Wire.write(verdieping);
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_1);
  Wire.write(verdieping);
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_2);
  Wire.write(verdieping);
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_3);
  Wire.write(verdieping);
  Wire.endTransmission();

  Wire.beginTransmission(SLAVE_4);
  Wire.write(verdieping);
  Wire.endTransmission();

  Wire.requestFrom(SLAVE_0, 1);
  while (Wire.available()) {
    byte d = byte(Wire.read());
    int knopBoven = d & 00000001;
    d = d >> 1;
    int knopBeneden = d & 00000001;
    //Serial.println(knopBoven);
    //Serial.println(knopBeneden);

    d = d >> 1;
    int f = d & 00000001;
    d = d >> 1;
    if (f == 1) {
      verdieping = d;
    }
    if (knopBoven == 1 || knopBeneden == 1) {
      knopOproep = d;
    }
  }
  //__________________________________________________________
  Wire.requestFrom(SLAVE_1, 1);
  while (Wire.available()) {
    byte d = byte(Wire.read());
    //Serial.println(d);
    int knopBoven = d & 00000001;
    d = d >> 1;
    //Serial.println(d);
    int knopBeneden = d & 00000001;
    //Serial.println(knopBoven);
    //Serial.println(knopBeneden);

    d = d >> 1;
    //Serial.println(d);
    int f = d & 00000001;
    //Serial.println(f);
    d = d >> 1;
    //Serial.println(d);
    if (f == 1) {
      verdieping = d;
    }
    if (knopBoven == 1 || knopBeneden == 1) {
      knopOproep = d;
    }
  }
  //__________________________________________
  Wire.requestFrom(SLAVE_2, 1);
  while (Wire.available()) {
    byte d = byte(Wire.read());

    int knopBoven = d & 00000001;
    d = d >> 1;
    int knopBeneden = d & 00000001;
    //Serial.println(knopBoven);
    //Serial.println("_____________");
    //Serial.println(knopBeneden);

    d = d >> 1;
    int f = d & 00000001;

    d = d >> 1;
    if (f == 1) {
      verdieping = d;
    }
    if (knopBoven == 0 || knopBeneden == 0) {
      knopOproep = d;
    }
  }
  //_______________________________________________________________
  Wire.requestFrom(SLAVE_3, 1);
  while (Wire.available()) {
    byte d = byte(Wire.read());
    //Serial.println(d);
    int knopBoven = d & 00000001;
    d = d >> 1;
    //Serial.println(d);
    int knopBeneden = d & 00000001;
    //Serial.println(knopBoven);
    //Serial.println(knopBeneden);

    d = d >> 1;
    //Serial.println(d);
    int f = d & 00000001;
    //Serial.println(f);
    d = d >> 1;
    //Serial.println(d);
    if (f == 1) {
      verdieping = d;
    }
    if (knopBoven == 1 || knopBeneden == 1) {
      knopOproep = d;
    }
  }
  //_____________________________________________________________
  Wire.requestFrom(SLAVE_4, 1);
  while (Wire.available()) {
    byte d = byte(Wire.read());

    int knopBoven = d & 00000001;
    d = d >> 1;
    int knopBeneden = d & 00000001;
    //Serial.println(knopBoven);
    //Serial.println(knopBeneden);

    d = d >> 1;
    int f = d & 00000001;
    //Serial.println(f);
    d = d >> 1;
    if (f == 1) {
      verdieping = d;
    }
    if (knopBoven == 1 || knopBeneden == 1) {
      knopOproep = d;
    }
  }
  //_________________________________________________________________________
  Serial.println("===============================");
  Serial.println(verdieping);
  Serial.println("===============================");
}

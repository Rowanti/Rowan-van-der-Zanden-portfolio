//verbonden pins
#define red_pin 3
#define green_pin 5
#define blue_pin 6
#define IR A0

//RGB waardes
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  // In-en outputs 
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  pinMode(IR, INPUT);
}

void loop() {
  // wanneer de sensor de hand waarneemt worde er random RGB waardes gestuurd
  if (analogRead(IR) < 100){
    RGB_send(random(255),random(255),random(255));
  } else {
    RGB_send(red,green,blue);
  }
  delay(100);
}

//RGB waardes opslaan en versturen
void RGB_send(int red_value, int green_value, int blue_value){
  red = red_value;
  green = green_value;
  blue = blue_value;
  analogWrite(red_pin, red_value);
  analogWrite(green_pin, green_value);
  analogWrite(blue_pin, blue_value);
}
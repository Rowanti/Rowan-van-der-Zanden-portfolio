#include <SoftwareSerial.h>
#define bluetoothRX 2 //2
#define bluetoothTX 3
SoftwareSerial mySerial(bluetoothRX, bluetoothTX);

String input;


void setup() {
  // Open serial communications and wait for port to open:
//  Serial.begin(38400);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  // Open serial communication for the Bluetooth Serial Port
//  mySerial.begin(9600);
//  mySerial.begin(38400);
  Serial.println("\n----Start----");
  mySerial.begin(9600);

  Serial.println("The Device started, now you can pair it with bluethooth!");
  Serial.println("Device Name: Haa..");
  Serial.println("BT MAC: ");
  
}

void loop() {
  
  // If any data is available at the Bluetooth Serial Port
  if (mySerial.available()) {
    // Write this data to the Serial Monitor (Arduino)
    Serial.write(mySerial.read());
//      Serial.println(mySerial.readStringUntil('\n'));
  }


  // If any data is sent via the Serial Monitor (Arduino)
  if (Serial.available()) {
    // Send this data via the Bluetooth Serial Port
//    mySerial.write(Serial.read());
    input = Serial.readStringUntil('\n');
    Serial.println(input);
    mySerial.println(input);
//    mySerial.write(Serial.read());
//    mySerial.println(Serial.readStringUntil('\n'));
    
  }
}

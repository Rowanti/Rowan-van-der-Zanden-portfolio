// ref: Examples > BluetoothSerial > SerialToSerialBT

//#include <SPI.h>
//#include "LoRa.h"
//
//int counter = 0;
//
//#define ss 15
//#define rst 4
//#define dio0 2
//---------

#include "BluetoothSerial.h"
#include "esp_bt_device.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


#define led 32
BluetoothSerial SerialBT;

String input;
char espData[20];
byte espReceive;
byte espWrite;


void printDeviceAddress() {
 
  const uint8_t* point = esp_bt_dev_get_address();
 
  for (int i = 0; i < 6; i++) {
 
    char str[3];
 
    sprintf(str, "%02X", (int)point[i]);
    Serial.print(str);
 
    if (i < 5){
      Serial.print(":");
    }
  }
}

void moveForward(){
  
}

void setup() {
//  Serial.begin(9600);
Serial.begin(115200);
//  while (!Serial);
//
//  Serial.println("LoRa Sender");
//  LoRa.setPins(ss, rst, dio0);
//  if (!LoRa.begin(433E6)) {
//    Serial.println("Starting LoRa failed!");
//    while (1);
//  }
//  -----
  pinMode(led, OUTPUT);
//  Serial.begin(115200);
  Serial.println("\n---Start---");
  SerialBT.begin("ESP32test"); //Bluetooth device name
  
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("Device Name: ESP32test");
  Serial.print("BT MAC: ");
  printDeviceAddress();
  Serial.println();
}

void loop() {
//  Serial.print("Sending packet: ");
//  Serial.println(counter);
//
//  // send packet
//  LoRa.beginPacket();
//  LoRa.print("hello ");
//  LoRa.print(counter);
//  LoRa.endPacket();
//
//  counter++;
//
//  delay(1000);

//  ------
  String ledOn = "Led-ON";
  String currentLine = " ";
   
  
  if (Serial.available()) {
//    String input = Serial.readStringUntil('\n');
//    SerialBT.write(Serial.read());
      SerialBT.readStringUntil('\n');
      espWrite = Serial.read();
     Serial.println("-----Write-----------");
      Serial.println(espWrite);
      Serial.println("----------------");

  }
  if (SerialBT.available()) {
//    Serial.write(SerialBT.read());
        String data = SerialBT.readStringUntil('\n');
        Serial.println(data);
      espReceive = SerialBT.read();
      Serial.println("-----Receive-----------");
      Serial.println(espReceive);
      Serial.println("----------------");
//      if(espReceive == 49){
//        Serial.println("kaas");
//        digitalWrite(led,HIGH);
//      }
//      else{
//        Serial.println("Geen kas");
//      }
    
/*
      //espReceive = SerialBT.read();
      Serial.println("----------------");
      Serial.println(SerialBT.read());
      Serial.println("----------------");
                 
     if(SerialBT.read() == 49 ){
    digitalWrite(led,HIGH);
    Serial.println("kaas");
  }
  else{
    digitalWrite(led,LOW);
  }
  */
  
  }  
  Serial.read();
  delay(20);
}

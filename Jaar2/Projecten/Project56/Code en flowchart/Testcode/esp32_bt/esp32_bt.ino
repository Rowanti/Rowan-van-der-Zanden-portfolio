// ref: Examples > BluetoothSerial > SerialToSerialBT

#include "BluetoothSerial.h"
#include "esp_bt_device.h"
#define RXp2 16
#define TXp2 17

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif


BluetoothSerial SerialBT;

String input;
char espData[20];
byte espReceive;
byte espWrite;
bool follow;


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

void setup() {

  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
  Serial.println("\n---Start---");
  SerialBT.begin("ESP32test"); //Bluetooth device name
  
  Serial.println("The device started, now you can pair it with bluetooth!");
  Serial.println("Device Name: ESP32test");
  Serial.print("BT MAC: ");
  printDeviceAddress();
  Serial.println();
}

void loop() {
  
  String currentLine = " ";
   
  Serial2.write("1");
  Serial.println("1");
  vTaskDelay(800);
  Serial2.write("2");
  Serial.println("2");
  vTaskDelay(800);

  if (SerialBT.available()) {

        String data = SerialBT.readStringUntil('\n');
        Serial.println(data);
        if(data == "beacon1"){
          Serial2.write("1");
          Serial.println("kaas");
        }else if(data == "beacon2"){
          Serial2.write("2");
        }else if(data == "beacon3"){
          Serial2.write("3");
        }else if(data == "beacon4"){
          Serial2.write("4");
        }else if(data == "stop"){
          Serial.write("9");
        }else if(data == "follow"){
          follow = true;

        }
        while(follow == true){
            //float coordinate = SerialBT.readStringUntil('\n');
            

            // if(coordinate = "nofollow"){
            //   break;
            // }
        }
  
  }  
 



  delay(20);
}

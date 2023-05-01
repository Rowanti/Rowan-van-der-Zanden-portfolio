
  
#include <SPI.h>
#include <LoRa.h> 
char number = '69';
//int pot = A0;
 
void setup() {
  Serial.begin(9600);
  //pinMode(pot,INPUT);
  int incoming = 0;
  while (!Serial);  
  Serial.println("LoRa Sender");
  if (!LoRa.begin(433E6)) { // or 915E6, the MHz speed of yout module
    Serial.println("Starting LoRa failed!");
    while (1);
  }
}
 
void loop() {
  //int val = map(analogRead(pot),0,1024,0,255);
    
    
    //LoRa.beginPacket();  
    //LoRa.print(number);
    //LoRa.endPacket();
    //



   

      LoRa.beginPacket();  
      LoRa.print("52.239857293578 , 4.34242323422 \n");
      LoRa.endPacket();
      delay(1000);


      
      
      
      

      
    

    
    
 
}

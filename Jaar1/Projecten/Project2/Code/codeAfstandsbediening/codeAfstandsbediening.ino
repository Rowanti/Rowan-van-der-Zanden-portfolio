//mac adress slave:
//3C:61:05:28:C3:6C {0x3C, 0x61, 0x05, 0x28, 0xC3, 0x6C}

//mac adress master:
//24:0A:C4:F9:D3:54 {0x24, 0x0A, 0xC4, 0xF9, 0xD3, 0x54}

#include <esp_now.h>
#include <WiFi.h>

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = {0x3C, 0x61, 0x05, 0x28, 0xC3, 0x6C};

// Structure example to send data
// Must match the receiver structure
typedef struct struct_message {
    int a;
    int b;
    int c;
    int d;
    int e;
} struct_message;

// Create a struct_message called myData
struct_message myData;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

#define knopje_a 27
#define knopje_b 26
#define knopje_c 32
#define knopje_d 35
#define knopje_e 34
int temp = 0;


void setup() {
  // Init Serial Monitor
  Serial.begin(115200);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  pinMode(knopje_a, INPUT);
  pinMode(knopje_b, INPUT);
  pinMode(knopje_c, INPUT);
  pinMode(knopje_d, INPUT);
  pinMode(knopje_e, INPUT);

}
 
void loop() {
  
  // Set values to send  
  if (digitalRead(knopje_a) == HIGH && temp == 0){
    if (myData.a == 1){
      myData.a = 0;
    }else{
      myData.a = 1;
    }
    temp = 1;
  }
  if (digitalRead(knopje_a) == LOW){
    temp = 0;
  }

  if (digitalRead(knopje_b) == HIGH){
    myData.b = 1;
  }else{
    myData.b = 0;
  }

  if (digitalRead(knopje_c) == HIGH){
    myData.c = 1;
  }else{
    myData.c = 0;
  }

  if (digitalRead(knopje_d) == HIGH){
    myData.d = 1;
  }else{
    myData.d = 0;
  }

  if (digitalRead(knopje_e) == HIGH){
    myData.e = 1;
  }else{
    myData.e = 0;
  }

  // Check if values are correct
  Serial.print("knopje_a: ");
  Serial.print(digitalRead(knopje_a));
  Serial.println(myData.a);
  Serial.print("knopje_b: ");
  Serial.print(digitalRead(knopje_b));
  Serial.println(myData.b);
  Serial.print("knopje_c: ");
  Serial.print(digitalRead(knopje_c));
  Serial.println(myData.c);
  Serial.print("knopje_d: ");
  Serial.print(digitalRead(knopje_d));
  Serial.println(myData.d);
  Serial.print("knopje_e: ");
  Serial.print(digitalRead(knopje_e));
  Serial.println(myData.e);
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
   
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  delay(500);
}
byte echoPins[] = {4, 6};
byte trigPins[] = {5, 7};

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  size_t n = sizeof(echoPins)/sizeof(echoPins[0]);
  for (int i=0;i<n;i++){
    pinMode(echoPins[i], INPUT);
  }
  for (int i=0;i<n;i++){
    pinMode(trigPins[i], OUTPUT);
  }
  Serial.println("Start of code");
}


float measure(int trigPin, int echoPin){
  long duration;
  int distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  // Displays the distance on the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");
  return distance;
}
void drive(){
  Serial.println("WE DRIVE FORWARDS");
}
void still(){
  Serial.println("OBJECT HELP");
}
void loop() {
  // put your main code here, to run repeatedly:
  size_t n = sizeof(echoPins)/sizeof(echoPins[0]);
  for (int i=0;i<n;i++){
    if(measure(trigPins[i], echoPins[i])>70){
      drive();
    } else{
      still();
    }
  }
  Serial.println("__________________________________");
  delay(200);
}

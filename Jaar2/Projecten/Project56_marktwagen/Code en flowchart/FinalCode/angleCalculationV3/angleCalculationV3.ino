// float x1 = 4.234511f;
// float y1 = 4.234510f;
// float x2 = 4.234510f;
// float y2 = 4.234511f;

float x1 = 11;
float y1 = 10;
float x2 = 10;
float y2 = 8.666666;
// x,y,x,y
int calAngle(float long1, float  lat1, float  long2, float  lat2){
  if(lat2 - lat1 == 0){
    if (long2>=long1){
      return 90;
    } else{
      return 270;
    }
  } else if(long2-long1==0){
    if (lat2>=lat1){
      return 0;
    } else {
      return 180;
    }
  } else if (long2 - long1 > 0) {
    if (lat2>lat1){
      return round(atan((long2-long1)/(lat2-lat1))* 57296/1000);
    } else {
      return 180 - abs(round(atan((long2-long1)/(lat2-lat1))* 57296/1000));
    }
  } else {
    if (lat2>lat1){
      return 360 - abs(round(atan((long2-long1)/(lat2-lat1))* 57296/1000));
    } else {
      return 180 + round(atan((long2-long1)/(lat2-lat1))* 57296/1000);
    }
  }
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(calAngle(x1, y1, x2, y2));
  delay(100);
}

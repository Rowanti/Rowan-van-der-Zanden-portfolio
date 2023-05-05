int currentAngle = 90;
int getAngle(double long1, double  lat1, double  long2, double  lat2) {
  unsigned long mult = 1000000000000000;
  unsigned long lo1= (long1- int(long1))*mult;
  unsigned long la1= (lat1- int(lat1))*mult;
  unsigned long lo2= (long2- int(long2))*mult;
  unsigned long la2= (lat2- int(lat2))*mult;
  Serial.println(la2);
  Serial.println(la1);
  if (lo2 - lo1 == 0) {
    if (la2 >= la1) {
      return 0;
    } else {
      return 180;
    }
  } else if(la2-la1==0){
    if (lo2>=lo1){
      Serial.println("test");
      return 90;
    } else {
      return 270;
    }
  } else if (lo2 - lo1 > 0) {
    return round(atan((la2-la1)/(lo2-lo1))* 57296 / 1000);
    // if (long2 - long1 >= 0) {
    //   return round((atan((long2 - long1) / (lat2 - lat1)))* 57296 / 1000);
    // } else {
    //   return round((atan((abs(long2 - long1)) / (lat2 - lat1)))*-1 * 57296 / 1000);
    // }
  } else {
    if (long2 - long1 >= 0) {
      return round(180 - (atan((long2 - long1) / (abs(lat2 - lat1)))) * 57296 / 1000);
    } else {
      return round((180 - (atan((long2 - long1) / (lat2 - lat1))) * 57296 / 1000) * -1);
    }
  }
}
// # lat = y
// # long = x
void setup() {
  Serial.begin(9600);
  
}
void loop() {
  Serial.println("______________________________");
  // Serial.println(getAngle(4.679730788228449, 51.885386406957075, 19.022418466905325, -58.71745847123175));
  // Serial.println(getAngle(4.679730788228449, 51.885386406957075, 21.144424696987727, 52.8534947032697));
  // Serial.println(getAngle(4.679730788228449, 51.885386406957075, 4.679730788228449, 52.885386406957075));
  // Serial.println(getAngle(4.679730788228449, 51.885386406957075, 5.679730788228449, 51.885386406957075));
  Serial.println(getAngle(4.55146,1.000000,6.011111111,1.885386406957075));
  Serial.println("______________________________");
  // int tempAngle = getAngle(4.4777417, 51.924419, 4.4777410, 51.924420);
  delay(1000);
}
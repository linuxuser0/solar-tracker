float waittime = 0.5;
float brightthresh;
int sensor = 0; //sensor port
float loc1[2];
float loc2[2];
int tachox = 1; //sensor port for tachomemter for x
int tachoy = 1; //sensor port for tachomemter for y
int iter = 0; //variable to hold # of times tracker has moved
float lat;
float threshold; //a plus or minus threshold for comparison of previous light values - should be relatively small

void setup(){
  Serial.begin(9600);
  calibrateBrightThresh();
  trackAndGetLocationOne();
  waitMin(waittime);
  trackAndGetLocationTwo();
  waitMin(waittime);
}

void loop(){
  trackWithEstimate(); //uses loc1 and loc2 to move to next location
  loc1[0] = loc2[0];
  loc1[1] = loc2[1]; 
  getLocationLocTwo(); //sets loc2 to current location 
  waitMin(waittime);
}

float findLightX(){ //points dish toward light in x dimension, returns x value (angle, 0 to 180)
  int sensorval = analogRead(sensor);
  int prevsensorval = 0;
  
  boolean motorright = false; //true for left, false for right for motor direction
  
  do{
    if(sensorval>prevsensorval+threshold){
      //right way
    }
    if(sensorval<prevsensorval-threshold){
      //wrong way
      motorright = !motorright;
    }
    turnXMotor(motorright); //true for left, false for right
  }while(sensorval < brightthresh);
  return getXDegree();
}

float findLightY(){ //points dish toward light in x dimension, returns x value (angle, 0 to 180)
  int sensorval = analogRead(sensor);
  int prevsensorval = 0;
  
  boolean motorright = false; //true for left, false for right for motor direction
  
  do{
    if(sensorval>prevsensorval+threshold){
      //right way
    }
    if(sensorval<prevsensorval-threshold){
      //wrong way
      motorright = !motorright;
    }
    turnYMotor(motorright); //true for left, false for right
  }while(sensorval < brightthresh);
  
  return getYDegree(); 
}

void turnXMotor(boolean direction){
  if(direction){ //left for true, right for false
    digitalWrite(2, HIGH);
    digitalWrite(3, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
  }
  else{
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, HIGH);
    digitalWrite(5, HIGH);
  }
}

void turnYMotor(boolean direction){
  if(direction){ //left for true, right for false
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
  }
  else{
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
  }
}

void stopXMotor(){
  digitalWrite(2, LOW);
  digitalWrite(3, LOW);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);  
}

void stopYMotor(){
  digitalWrite(6, LOW);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
  digitalWrite(9, LOW);  
}

void turnXAngle(float angle){
  if(angle > getXDegree()){ //motor should turn right
    turnXMotor(false);
    while(angle > getXDegree());
    stopXMotor();
  }
  else if(angle < getXDegree()){
    turnXMotor(false);
    while(angle > getXDegree());
    stopXMotor();
  }
}

void turnYAngle(float angle){
  if(angle > getYDegree()){ //motor should turn right
    turnYMotor(false);
    while(angle > getYDegree());
    stopYMotor();
  }
  else if(angle < getYDegree()){
    turnYMotor(false);
    while(angle > getYDegree());
    stopYMotor();
  }
}

void trackWithEstimate(){
  turnXAngle(2*loc2[0]-loc1[0]);
  turnYAngle(2*loc2[1]-loc1[1]);
}

void calibrateBrightThresh(){
  digitalWrite(13, HIGH);
  while(digitalRead(12) == LOW){} //button press on pin 12
  brightthresh = analogRead(sensor);
  digitalWrite(13, LOW);
}

void waitMin(float time){ //waits "time" in minutes
  delay(time*1000*60);
}

float getXDegree(){
  analogRead(1)*(360/1023); //range from 0-1023 times degrees per 1023 constant
}

float getYDegree(){
  analogRead(2)*(360/1023); //range from 0-1023 times degrees per 1023 constant
}

void getLocationLocTwo(){
  //tomake!
}

void trackAndGetLocationOne(){ //points dish toward light and sets "loc" to the location [x, y]
  float x = findLightX();
  float y = findLightY();
  loc1[0] = x;
  loc1[1] = y;
}

void trackAndGetLocationTwo(){
  float x = findLightX();
  float y = findLightY();
  loc2[0] = x;
  loc2[1] = y;
}

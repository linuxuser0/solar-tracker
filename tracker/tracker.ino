void setup(){
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  Serial.begin(9600);
}

int result;
int lastresult;
  
void loop(){
  pointMotorA();
  pointMotorB();
}

void motorAForward(){
  digitalWrite(4, HIGH);
  digitalWrite(2, HIGH);
  digitalWrite(3, LOW);
  digitalWrite(5, LOW);
}

void motorABackward(){
  digitalWrite(4, LOW);
  digitalWrite(2, LOW);
  digitalWrite(3, HIGH);
  digitalWrite(5, HIGH);
}

void motorBForward(){
  digitalWrite(6, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(9, LOW);
}

void motorBBackward(){
  digitalWrite(6, LOW);
  digitalWrite(8, LOW);
  digitalWrite(7, HIGH);
  digitalWrite(9, HIGH);
}

void brakeA(){
  digitalWrite(2, HIGH);
  digitalWrite(3, HIGH);
  digitalWrite(4, LOW);
  digitalWrite(5, LOW);
}

void brakeB(){
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, LOW);
  digitalWrite(8, LOW);
}

int readInput(){
  return analogRead(A2);
}

void writeInput(){
  Serial.println(result);
  digitalWrite(11, result/4);
}

void pointMotorA(){
  result = -1;
  do{
    lastresult = result;
    result = readInput();
    motorBForward();
  }while(result>lastresult);
}

void pointMotorB(){
  readInput();
}

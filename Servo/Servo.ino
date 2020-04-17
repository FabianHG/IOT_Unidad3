#include <Servo.h>
Servo servoMotor;

void setup() {
  // put your setup code here, to run once:
  servoMotor.attach(5);
  pinMode(11, INPUT);
  pinMode(2, INPUT);
  pinMode(8, INPUT);
  pinMode(9, OUTPUT);

}

void loop() {
  if(digitalRead(2)==HIGH){
      servoMotor.write(180);
  }else{
      servoMotor.write(0);
  }

  if(digitalRead(8)==HIGH){
      digitalWrite(9, HIGH);
  }else{
      digitalWrite(9, LOW);
  }

  if(digitalRead(11)==HIGH){
      digitalWrite(10, HIGH);
  }else{
      digitalWrite(10, LOW);
  }
}

#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoZ;
Servo servoClamp;

//Mid point values
int xDeg=85;
int yDeg=45;
int zDeg=70;
int clampDeg=40;

void setup()
{
  pinMode(A0,INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(A3,INPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(9,OUTPUT);

  servoX.attach(3);
  servoY.attach(5);
  servoZ.attach(6);
  servoClamp.attach(9);

  servoX.write(xDeg);
  servoY.write(yDeg);
  servoZ.write(zDeg);
  servoClamp.write(clampDeg);

  Serial.begin(9600);
}

void loop()
{
  int leftJoyX=analogRead(A0);
  int leftJoyY=analogRead(A3);
  int rightJoyX=analogRead(A2);
  int rightJoyY=analogRead(A1);

  delay(5);

  if(leftJoyX<40) xDeg-=15;
  else if(leftJoyX<200) xDeg-=10;
  else if(leftJoyX>1004) xDeg+=15;
  else if(leftJoyX>820) xDeg+=10;
  
  if(rightJoyY<40) yDeg-=12;
  else if(rightJoyY<200) yDeg-=7;
  else if(rightJoyY>1004) yDeg+=12;
  else if(rightJoyY>820) yDeg+=7;
  
  if(rightJoyX<40) zDeg+=12;
  else if(rightJoyX<200) zDeg+=7;
  else if(rightJoyX>1004) zDeg-=12;
  else if(rightJoyX>820) zDeg-=7;
  
  if(leftJoyY<250) clampDeg+=45;
  else if(leftJoyY>800) clampDeg-=45;

  xDeg=min(150,max(0,xDeg));
  yDeg=min(55,max(10,yDeg));
  zDeg=min(100,max(40,zDeg));
  clampDeg=min(180,max(40,clampDeg));

  servoX.write(xDeg);
  servoY.write(yDeg);
  servoZ.write(zDeg);
  servoClamp.write(clampDeg);

  delay(50);

  Serial.print("xDeg: ");
  Serial.print(xDeg);
  Serial.print("-");
  Serial.print(leftJoyX);
  Serial.print(", yDeg: ");
  Serial.print(yDeg);
  Serial.print("-");
  Serial.print(rightJoyY);
  Serial.print(", zDeg: ");
  Serial.print(zDeg);
  Serial.print("-");
  Serial.print(rightJoyX);
  Serial.print(", clampDeg: ");
  Serial.print(clampDeg);
  Serial.print("-");
  Serial.println(leftJoyY);
}

#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoZ;
Servo servoClamp;

// Mid point angles, change as needed
int xDeg = 145;
int yDeg = 25;
int zDeg = 55;
int clampDeg = 40; 

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);

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

void loop() {
  if (Serial.available() > 0) {
    char command = Serial.read();

    if (command == 'U') {
      zDeg -= 15;
    } else if (command == 'D') {
      zDeg += 15;
    } else if (command == 'F') {
      yDeg += 15;
    } else if (command == 'B') {
      yDeg -= 15;
    } else if (command == 'L') {
      xDeg -= 25;
    } else if (command == 'R') {
      xDeg += 25;
    } else if (command == 'O') {
      clampDeg += 40;
    } else if (command == 'C') {
      clampDeg -= 40;
    }

    // Minimum and Maximum angles, change as needed
    xDeg = min(150, max(0, xDeg));
    yDeg = min(55, max(10, yDeg));
    zDeg = min(65, max(30, zDeg));
    clampDeg = min(0, max(40, clampDeg));

    servoX.write(xDeg);
    servoY.write(yDeg);
    servoZ.write(zDeg);
    servoClamp.write(clampDeg);

    Serial.print("xDeg: ");
    Serial.print(xDeg);
    Serial.print(", yDeg: ");
    Serial.print(yDeg);
    Serial.print(", zDeg: ");
    Serial.print(zDeg);
    Serial.print(", clampDeg: ");
    Serial.println(clampDeg);

    delay(50);
  }
}

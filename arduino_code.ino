#include <Servo.h>

Servo servoX;
Servo servoY;
Servo servoZ;

// Mid point angles, change as required for your servos
int xDeg = 120;
int yDeg = 25;
int zDeg = 40;

void setup() {
  pinMode(3, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);

  servoX.attach(3);
  servoY.attach(5);
  servoZ.attach(6);

  servoX.write(xDeg);
  servoY.write(yDeg);
  servoZ.write(zDeg);

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
    }

    // Minimum and Maximum angles, change as required for your servos
    xDeg = min(150, max(0, xDeg));
    yDeg = min(55, max(10, yDeg));
    zDeg = min(100, max(40, zDeg));

    servoX.write(xDeg);
    servoY.write(yDeg);
    servoZ.write(zDeg);

    Serial.print("xDeg: ");
    Serial.print(xDeg);
    Serial.print(", yDeg: ");
    Serial.print(yDeg);
    Serial.print(", zDeg: ");
    Serial.println(zDeg);

    delay(50);
  }
}

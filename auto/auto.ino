#include <Servo.h> 

Servo servo1;
Servo servo2;

void setup() 
{ 
  servo1.attach(9);
  servo2.attach(10);
  servo1.write(90);
  servo2.write(90);
} 

void loop() {} 

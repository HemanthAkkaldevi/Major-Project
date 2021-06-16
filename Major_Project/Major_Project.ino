#include <Servo.h>


int pot_pin_bottom = A1;
int pot_pin_joint1 = A0;



int value_bottom;
int value_joint1;



Servo servo_bottom;
Servo servo_joint1;


void setup() {
  servo_bottom.attach(7);
  servo_joint1.attach(3);
  Serial.begin(9600);
}

void loop() {
  int pot_inputs[4];
  
  pot_inputs[1] = analogRead(pot_pin_bottom);
  pot_inputs[2] = analogRead(pot_pin_joint1);
  


  
  value_bottom = map(pot_inputs[1], 110, 800, 180, 0);
  value_joint1 = map(pot_inputs[2], 110, 800, 180, 0);


  
  servo_bottom.write(value_bottom);
  servo_joint1.write(value_joint1);

  delay(5);
}

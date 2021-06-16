#include <Servo.h>
#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();
double temp_amb;
double temp_obj;

int pot_pin_claw = A0;
int pot_pin_bottom = A1;
int pot_pin_joint1 = A2;
int pot_pin_joint2 = A3;

int value_claw;
int value_bottom;
int value_joint1;
int value_joint2;

#define SERVO2_PIN 2
Servo servo2;
#define SERVO3_PIN 5
Servo servo3;
Servo servo_claw;
Servo servo_bottom;
Servo servo_joint1;
Servo servo_joint2;

//ultrasonic sensor
const int trig1Pin = 9;
const int echo1Pin = 8;
int sound1 = 250;

//ultrasonic sensor
const int trig2Pin = 10;
const int echo2Pin = 13;
int sound2 = 250;

//buzzer
 int buzzer = 12;

void setup() {
  
  //setup for ultrasonic sensor
  pinMode(trig1Pin, OUTPUT);
  pinMode(echo1Pin, INPUT);
  servo2.attach(SERVO2_PIN);
  servo2.write(0);

  //setup for ultrasonic sensor
  pinMode(trig2Pin, OUTPUT);
  pinMode(echo2Pin, INPUT);
  servo3.attach(SERVO3_PIN);
  servo3.write(0);
  
  //setup for buzzer
  pinMode(buzzer, OUTPUT);

  
  servo_claw.attach(4);
  servo_bottom.attach(7);
  servo_joint1.attach(3);
  servo_joint2.attach(6);
  Serial.begin(9600);


  pinMode(12,OUTPUT);// Connect buzzer at D8

  //Initialize MLX90614
  mlx.begin();
  digitalWrite(12,LOW);
}

void loop() {

    //Reading room temperature and object temp
  //for reading Fahrenheit values, use
  //mlx.readAmbientTempF() , mlx.readObjectTempF() )
  temp_amb = mlx.readAmbientTempF();
  temp_obj = mlx.readObjectTempF()+7;
  if(temp_obj > 102) {
   digitalWrite(12,HIGH);
}
  else{
    digitalWrite(12,LOW);
  }

  //Serial Monitor
  Serial.print("Room Temp = ");
  Serial.println(temp_amb);
  Serial.print("Object temp = ");
  Serial.println(temp_obj); 

  //Activating Ultrasonic sensor for activating Dustbin
  long duration, distance;
  digitalWrite(trig1Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig1Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig1Pin, LOW);
  duration = pulseIn(echo1Pin, HIGH);
  distance = (duration/2) / 29.1;
  if (distance < 10) {
  Serial.println("Dustbin Activated");
  servo2.write(90);
  delay(2000);
  servo2.write(0);
  }

    //Activating Ultrasonic sensor for activating Dustbin
  long duration1, distance1;
  digitalWrite(trig2Pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trig2Pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig2Pin, LOW);
  duration1 = pulseIn(echo2Pin, HIGH);
  distance1 = (duration1/2) / 29.1;
  if (distance1 < 10) {
  Serial.println("Dustbin Activated");
  servo3.write(90);
  delay(2000);
  servo3.write(0);

  }
  
  int pot_inputs[4];
  pot_inputs[0] = analogRead(pot_pin_claw);
  pot_inputs[1] = analogRead(pot_pin_bottom);
  pot_inputs[2] = analogRead(pot_pin_joint1);
  pot_inputs[3] = analogRead(pot_pin_joint2);


  value_claw = map(pot_inputs[0], 110, 800, 180, 0);
  value_bottom = map(pot_inputs[1], 110, 800, 180, 0);
  value_joint1 = map(pot_inputs[2], 110, 800, 180, 0);
  value_joint2 = map(pot_inputs[3], 110, 800, 180, 0);

  servo_claw.write(value_claw);
  servo_bottom.write(value_bottom);
  servo_joint1.write(value_joint1);
  servo_joint2.write(value_joint2);

}

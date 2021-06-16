#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

//defining the RFID Reader 
#define SS_PIN 10
#define RST_PIN 9
#define ACCESS_DELAY 2000
#define DENIED_DELAY 1000
MFRC522 mfrc522(SS_PIN, RST_PIN); 

//defining servomotors
#define SERVO_PIN 2
Servo servo1; // servomotor for door access
Servo tap_servo;
int sensor_pin = 4;
int tap_servo_pin =5;
int val;

//buzzer
 int buzzer = A0;

void setup(){
  pinMode(sensor_pin,INPUT);
  tap_servo.attach(tap_servo_pin);

   //setup for RFID reader
  Serial.begin(9600);   // Initiate a serial communication
  SPI.begin();          // Initiate  SPI bus
  mfrc522.PCD_Init();   // Initiate MFRC522

  servo1.attach(SERVO_PIN);
  servo1.write( 0 );
  delay(7500);
  servo1.write( 0 );
  Serial.println("Put your card to the reader");
  Serial.println();



 //setup for buzzer
  pinMode(buzzer, OUTPUT);
  
}

void loop(){
  val = digitalRead(sensor_pin);

  if (val==0)
  {tap_servo.write(40);
  }
  if (val==1)
  {tap_servo.write(180);
    }


 // Looking for cards for RFID door access
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "33 1C DA 02") //change here the UID of the card
  {
    Serial.println("Authorized access");
    Serial.println("Person is not infected.");
    Serial.println();
    servo1.write( 180 );
    delay(4500);
    servo1.write( 0 );
  }
 
  else   
  {
    Serial.println(" Access denied");
    Serial.println("Person seems infected.");
    delay(DENIED_DELAY);
    digitalWrite(A0,HIGH);
    delay(1000);
    digitalWrite(A0,LOW);
  }   
}

#include <Wire.h>
#include <Adafruit_MLX90614.h>
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
const int buzzer=12;
const int threshold=104;

void setup() {
  Serial.begin(9600); 
  pinMode(12, OUTPUT);
  mlx.begin();  
}
void loop() {
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempC()); 
  Serial.print("*C\tObject = "); Serial.print(mlx.readObjectTempC()+7); Serial.println("*C"); // The value +7 was arrived at by trial and error, by checking on normal individuals and adjusting the reading to consistently show 37 degrees C or 98 degrees F
  Serial.print("Ambient = "); Serial.print(mlx.readAmbientTempF()); 
  Serial.print("*F\tObject = "); Serial.print(mlx.readObjectTempF()+11); Serial.println("*F"); // The value +7 was arrived at by trial and error, by checking on normal individuals and adjusting the reading to consistently show 37 degrees C or 98 degrees F
  Serial.println();
    if (mlx.readObjectTempF()+11>threshold){
    digitalWrite(buzzer, HIGH);
  } else {
    digitalWrite(buzzer, LOW);
  }
  delay(1000);
}

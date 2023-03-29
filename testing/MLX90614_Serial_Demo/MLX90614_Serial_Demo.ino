#include <Wire.h> 
#include <SparkFunMLX90614.h>

IRTherm therm; 

void setup(){
  Serial.begin(9600);
  therm.begin(); 
  therm.setUnit(TEMP_C); 
}

void loop(){  
  if (therm.read()){
    Serial.print("Object: " + String(therm.object(), 2));
    Serial.write("°"); 
    Serial.println("C");
    Serial.print("Ambient: " + String(therm.ambient(), 2));
    Serial.write("°"); 
    Serial.println("C");
    Serial.println();
  }
  delay(500);
}

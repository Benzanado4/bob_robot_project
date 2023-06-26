#include <Servo.h>

Servo myservo; 

void setup(){
    Serial.begin(115200);
    myservo.attach(22);
}

void loop(){
    for (int i = 85; i > 30; i--){
        myservo.write(i);
        delay(200);
        Serial.println(i);
    }    
}

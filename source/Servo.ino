#include <Servo.h>

Servo myservo; 
#define SERVO_PIN 22

void setupServo(){
    myservo.attach(SERVO_PIN);
    moveServo(30); 
    #if defined(DEVMODE)
        Serial.println("SERVO setup");
    #endif
}

void moveServo(byte angle){
    myservo.write(angle);
}

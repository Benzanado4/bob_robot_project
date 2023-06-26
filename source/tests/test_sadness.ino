/*
Sadness movements
*/
#include <L298N.h>

const uint8_t ENA = 3; 
const uint8_t ENB = 5; 
const uint8_t IN1 = 8; 
const uint8_t IN2 = 9;  
const uint8_t IN3 = 12;  
const uint8_t IN4 = 13;  

const uint8_t MINSPEED = 30;
const uint8_t MEDIUMSPEED = 100;
const uint8_t MAXSPEED = 255;
int delay_time = 1000;

L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, false, MINSPEED); 

void setup(){
    Serial.begin(9600);
}

void loop(){
    Serial.println("BACKWARD SLOW MOVEMENT");
    driver.backward(MINSPEED, delay_time);
    driver.stop(false, delay_time); // stop without brakes
}

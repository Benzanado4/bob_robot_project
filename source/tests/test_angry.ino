/*Angry
Simply a fast straight movement forward toward you (a sort of charge) than 
*/

#include <L298N.h>

const uint8_t ENA = 3; 
const uint8_t ENB = 5; 
const uint8_t IN1 = 8; 
const uint8_t IN2 = 9; 
const uint8_t IN3 = 12;
const uint8_t IN4 = 13;

const uint8_t MINSPEED = 200;
const uint8_t MEDIUMSPEED = 100;
const uint8_t MAXSPEED = 255;
int delay_time = 2000;

L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, false, MINSPEED); 

void setup(){
Serial.begin(9600);
}

void loop(){
 
Serial.println("FORWARD movement");
driver.forward(MAXSPEED, delay_time);
driver.stop(true, delay_time); // stop with brakes

Serial.println("BACKWARD movement");
driver.drive(driver.BACKWARD, MAXSPEED, 100, delay_time);
driver.drive(driver.STOP, 0, 0, delay_time); // stop without brakes

}

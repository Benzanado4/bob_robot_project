/* Fear 
Simply a short straight low movement backward, than stops for 1 second, then do a (random degree) 
rotation toward left or toward right,then fast movement
*/

#include <L298N.h>

long randomVal;
const uint8_t ENA = 3; 
const uint8_t ENB = 5; 
const uint8_t IN1 = 7; 
const uint8_t IN2 = 8; 
const uint8_t IN3 = 12;  
const uint8_t IN4 = 13;  

const uint8_t MINSPEED = 40;
const uint8_t MEDIUMSPEED = 100;
const uint8_t MAXSPEED = 255;
int delay_time_1 = 1000;
int delay_time_2 = 2000;
int delay_time_3 = 3000;

L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, false, MINSPEED); 

void leftStrangeMovement(){
    Serial.println("FORWARD LEFT movement");
    driver.drive(driver.FORWARD_L, MEDIUMSPEED, 40, random(800,2000));
}
  
void rightStrangeMovement(){
  Serial.println("FORWARD RIGHT movement");
  driver.drive(driver.FORWARD_R, MEDIUMSPEED, 40, random(800,2000));
}

void setup(){
    Serial.begin(9600);
    randomSeed(analogRead(0));
}

void loop(){  
    Serial.println("BACKWARD movement");
    driver.backward(MINSPEED, delay_time_1);
    driver.stop(false, delay_time_1);
    int randomNum;
    randomNum=random(0, 1);
    if(randomNum=0)
        leftStrangeMovement(); 
    else
        rightStrangeMovement();

    Serial.println("FORWARD movement");
    driver.forward(MAXSPEED, delay_time_2);
    driver.stop(true, delay_time_2); // stop with brakes
}



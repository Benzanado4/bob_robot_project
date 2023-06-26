/* Happiness movements 
*/
#include <L298N.h>

const uint8_t ENA = 3; 
const uint8_t ENB = 5; 
const uint8_t IN1 = 8; 
const uint8_t IN2 = 9;  
const uint8_t IN3 = 12;  
const uint8_t IN4 = 13;  

const uint8_t MINSPEED = 150;
const uint8_t MAXSPEED = 255;
int delay_time = 2000;

L298N driver(ENA, IN1, IN2, IN3, IN4, ENB, false, MINSPEED); 

void happyMovement0(){
    // trajectory driving
    Serial.println("Happy0 FORWARD RIGHT movement");
    driver.drive(driver.FORWARD_R, MINSPEED, 70, 1000);
    Serial.println("Happy FORWARD LEFT movement");
    driver.drive(driver.FORWARD_L, MINSPEED, 70, 1000);
    driver.stop(false, delay_time); // stop without brakes
    Serial.println("FORWARD RIGHT movement");
    driver.drive(driver.FORWARD_R, MINSPEED, 40, 1000);
    Serial.println("FORWARD LEFT movement");
    driver.drive(driver.FORWARD_L, MINSPEED, 40, 1000);
    driver.stop(false, delay_time); // stop without brakes 
}

void happyMovement1(){
    // very "shaken" trajectory driving 
    Serial.println("HAPPY1_BACKWARD LEFT");
    driver.drive(driver.BACKWARD_L, MAXSPEED, 70, 1000);
    Serial.println("HAPPY1_BACKWARD RIGHT");
    driver.drive(driver.BACKWARD_R, MAXSPEED, 70, 1000);
    Serial.println("HAPPY1_BACKWARD LEFT");
    driver.drive(driver.BACKWARD_L, MAXSPEED, 70, 1000);
    Serial.println("HAPPY1_BACKWARD RIGHT");
    driver.drive(driver.BACKWARD_R, MAXSPEED, 70, 1000);
    driver.stop(false, delay_time); // stop without brakes 
}

void happyMovement2(){
    Serial.println("HAPPY2_FORWARD RIGHT mov");
    driver.drive(driver.FORWARD_R, MINSPEED, 70, 1000);
    Serial.println("HAPPY2_BACKWARD LEFT mov");
    driver.drive(driver.BACKWARD_L, MINSPEED, 70, 1000);
    Serial.println("HAPPY2_FORWARD LEFT mov");
    driver.drive(driver.FORWARD_L, MINSPEED, 70, 1000);
    Serial.println("HAPPY2_BACKWARD RIGHT RIGHT mov");
    driver.drive(driver.BACKWARD_R, MINSPEED, 40, 1000);
}

void happyMovement3(){
    Serial.println("HAPPY3_FORWARD RIGHT mov");
    driver.drive(driver.FORWARD_R, MINSPEED, 70, 3000);
    driver.stop(false, delay_time); // stop without brakes
}



void setup(){
    Serial.begin(9600);
}

void loop(){
    int randomNum;
    randomNum=random(0, 4);
    Serial.println(randomNum);
    delay(1000);

    switch (randomNum){

    case 0: 
    Serial.println("daje_0");
    happyMovement0();
    break;
    case 1: 
    Serial.println("daje_1");
    happyMovement1();
    break;
    case 2: 
    Serial.println("daje_2");
    happyMovement2();
    break;
    case 3: 
    Serial.println("daje_3");
    happyMovement3();
    break;
 }

}  
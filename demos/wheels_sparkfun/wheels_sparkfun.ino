#include <SparkFun_TB6612.h>

#define AIN1 25
#define BIN1 26
#define AIN2 27
#define BIN2 24
#define PWMA 6
#define PWMB 7
#define STBY 28

const int offsetA = 1;
const int offsetB = 1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

void setup(){}

void loop(){
    motor1.drive(255, 1000);
    motor1.drive(-255, 1000);
    motor1.brake();
    delay(1000);
    motor2.drive(255, 1000);
    motor2.drive(-255, 1000);
    motor2.brake();
    delay(1000);

    forward(motor1, motor2, 150);
    delay(1000);

    back(motor1, motor2, -150);
    delay(1000);

    brake(motor1, motor2);
    delay(1000);

    left(motor1, motor2, 100);
    delay(1000);
    right(motor1, motor2, 100);
    delay(1000);

    brake(motor1, motor2);
    delay(1000);
}

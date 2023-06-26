#include <Servo.h>

Servo base;
Servo head;

int pos = 0;

void setup(){
    base.attach(9);
    head.attach(8);
}

void loop(){
    sadness();
    head.write(20);
    delay(500);
    for (pos = 0; pos <= 60; pos += 1){
        head.write(pos);
        delay(20);
    }
    for (pos = 60; pos >= 0; pos -= 1){
        head.write(pos);
        delay(20);
    }
    for (pos = 40; pos <= 60; pos += 1){
        base.write(pos);
        delay(15);
    }
    for (pos = 60; pos >= 0; pos -= 1){
        base.write(pos);
        delay(15);
    }
    for (pos = 0; pos <= 40; pos += 1){
        base.write(pos);
        delay(15);
    }
    base.write(40);
    delay(2000);
    head.write(40);
    delay(2000);
    base.write(0);
    delay(1000);
    head.write(0);
    delay(1000);
    
    for (pos = 0; pos <= 60; pos +=1){
        base.write(pos);
        delay(10);
        head.write(pos);
        delay(10);
    }
    for (pos = 60; pos <= 0; pos +=1){
        base.write(pos);
        delay(10);
        head.write(pos);
        delay(10);
    }
    for (pos = 0; pos <= 180; pos += 1){ // from 0 degrees to 180 degrees, in steps of 1 degree
        myservo.write(pos);              
        delay(15);                       
    }
    for (pos = 180; pos >= 0; pos -= 1){ // from 180 degrees to 0 degrees
        myservo.write(pos);              
        delay(15);                       
    }
}

void sadness(){
    for (pos = 60; pos >= 0; pos -= 1){
        head.write(pos);
        delay(20);
    }
    for (int i = 0; i < 5; i++){
        for (pos = 40; pos <= 60; pos += 1){
            base.write(pos);
            delay(15);
        }
        for (pos = 60; pos >= 0; pos -= 1){
            base.write(pos);
            delay(15);
        }
        for (pos = 0; pos <= 40; pos += 1){
            base.write(pos);
            delay(15);
        }
    }
    for (pos = 0; pos <=60; pos +=1){
        head.write(pos);
        delay(20);
    }
}
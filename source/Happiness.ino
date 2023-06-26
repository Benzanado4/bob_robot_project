#include <Servo.h>

Servo base;
Servo head;

int pos = 0;

void happiness(){
    for (pos = 60; pos>=20; pos-=1){
        head.write(pos);    
        delay(13);
    }
    for (pos = 20; pos <= 80; pos+=1){
        head.write(pos);
        delay(13);
    }
    for (pos = 80; pos >=60; pos-=1){
        head.write(pos);
        delay(13);
    }
}

void setup(){
    base.attach(9);
    head.attach(8);
}

void loop(){
    happiness();
}
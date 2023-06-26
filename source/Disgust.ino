#include <Servo.h>

//create servo objects to control head and base
Servo base;
Servo head;

int pos = 0;

void disgust(){
    int pos_head = 60;
    for (pos = 20; pos <= 110; pos += 1){
        base.write(pos);
        delay(8);
        if (pos_head > 0){
            head.write(pos_head);
            delay(8);
            pos_head -= 1;
        }
    }
    delay(4000);
    for (pos = 110; pos >= 20; pos -= 1){
        base.write(pos);
        delay(15);
    }
    for (pos = 0; pos <= 60; pos += 1){
        head.write(pos);
        delay(15);
    }
}

void setup(){
    base.attach(9);
    head.attach(8);
}

void loop(){
    disgust();
}
#include <TFT.h> 
#include <SPI.h>

#define CS   9
#define DC   8
#define RESET 7

TFT screen = TFT(CS, DC, RESET);

void cry(){
    int tearPos = screen.height() / 2, offset = 55;
    screen.background(0, 0, 0);
    screen.fill(255, 255, 255);
    screen.circle(screen.width() / 2, screen.height() / 2, 50);
    delay(1000);

    screen.background(0, 0, 0);
    screen.stroke(127, 127, 127);
    screen.fill(255, 255, 255);
    screen.rect(screen.width() / 2 - 50, screen.height() / 2 - 10, 100, 20);
    delay(500);

    for (int i = 0; i < 5; i++){
        while (tearPos < screen.height() + 10){
          screen.stroke(0, 0, 0);
          screen.fill(0, 0, 0);
          screen.circle(screen.width() / 2 + offset, tearPos, 5);
          delayMicroseconds(1);
          tearPos += 1;
          screen.fill(255, 127, 127);
          screen.circle(screen.width() / 2 + offset, tearPos, 5);
          delayMicroseconds(1);
        }
        delay(200);
        tearPos = screen.height() / 2;
    }
}

void wink(){
  screen.background(0, 0, 0);
  screen.stroke(127, 127, 127);
  screen.fill(255, 255, 255);
  screen.circle(screen.width() / 2, screen.height() / 2, 50);
  delay(500);

  screen.background(0, 0, 0);
  screen.stroke(127, 127, 127);
  screen.fill(255, 255, 255);
  screen.rect(screen.width() / 2 - 50, screen.height() / 2 - 10, 100, 20);
  delay(100);

  screen.background(0, 0, 0);
  screen.stroke(127, 127, 127);
  screen.fill(255, 255, 255);
  screen.circle(screen.width() / 2, screen.height() / 2, 50);
  delay(100);
}

void neutral (){
  screen.background(0, 0, 0);
  screen.fill(255, 255, 255);
  screen.circle(screen.width() / 2, screen.height() / 2, 50);
  delay(500);
}
// Input 1
void happy (){
  Serial.println("I am happy!");
  screen.background(0, 0, 0);
  screen.fill(0, 255, 255);
  screen.circle(screen.width() / 2, screen.height() / 2, 50);
  screen.fill(0, 0, 0);
  screen.circle(screen.width() / 2, screen.height() / 2, 40);
  screen.rect(0, screen.height() / 2, screen.width(), screen.height() / 2);
  delay(1000);
  neutral();
}
// Input 2
void sad (){
  Serial.println("I am sad...");
  screen.background(0, 0, 0);
  screen.fill(255, 0, 0);
  screen.rect(screen.width() * 0.2, screen.height() * 0.2, screen.width() * 0.6, screen.height() * 0.15);
  screen.circle(screen.width() * 0.78, screen.height() * 0.5, 10);
  screen.circle(screen.width() * 0.8, screen.height() * 0.82, 10);
  delay(1000);
  neutral();
}
// Input 3
void angry (){
  Serial.println("I AM ANGRY!!!!!!");
  screen.background(0, 0, 0);
  screen.fill(0, 0, 255);
  screen.circle(screen.width() * 0.4, screen.height() * 0.6, 20);
  screen.stroke(0, 0, 255);
  for (int i = 0; i < 20; i++){
    screen.line(screen.width() * 0.4 + i, screen.height() * 0.6 - 20 + i / 2,
                screen.width() * 0.7 + i, screen.height() * 0.2 + i / 2);
  }
  screen.stroke(0, 0, 0);
  delay(1000);
  neutral();
}
// Input 4
void scared (){
  Serial.println("I'm scared");
  screen.background(0, 0, 0);
  screen.fill(128, 0, 128);
  screen.circle(screen.width() / 2, screen.height() / 2, 50);
  screen.fill(0, 0, 0);
  screen.circle(screen.width() / 2, screen.height() / 2, 30);
  screen.fill(128, 0, 128);
  screen.circle(screen.width() / 2, screen.height() / 2, 10);
  delay(1000);
  neutral();
}
// Input 5
void disgusted (){
    screen.background(0, 0, 0);
    screen.fill(0, 255, 0);
    screen.stroke(0, 255, 0);
    int mov = 10;
    for (int i = 0; i < mov; i++){
    screen.line(screen.width() * 0.2 + i / 2, screen.height() * 0.7 + i / 2,
                screen.width() * 0.7 - i / 2, screen.height() * 0.5);
    }
    for (int i = 0; i < mov; i++){
    screen.line(screen.width() * 0.3 + mov - i, screen.height() * 0.2,
                screen.width() * 0.6 + mov - i, screen.height() * 0.5 + i / 2);
    }
    screen.stroke(0, 0, 0);
    delay(5000);
    neutral();
}

void setup(){
    Serial.begin(9600);
    screen.begin();
    screen.background(0, 0, 0);
    screen.stroke(0, 0, 0);
    screen.fill(255, 255, 255);
    screen.circle(screen.width() / 2, screen.height() / 2, 50);
    Serial.println("I am ready");
}

void loop(){
    char in = '0';

    if (Serial.available() > 0){
        in = Serial.read();
        Serial.print("Recieved ");
        Serial.println(in);
    }

    switch (in){
        case '1':
        sad();
        break;
        case '2':
        happy();
        break;
        case '3':
        angry();
        break;
        case '4':
        scared();
        break;
        case '5':
        disgusted();
        break;
    }
}
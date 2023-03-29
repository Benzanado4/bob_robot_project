#define N1 2
#define N2 3
#define N3 4
#define N4 5

void neutral(){
    stopAll();
}

void sad(){
    Serial.println("Sad");
    reverse();
    delay(500);
    stopAll();
}

void happy(){
    forward();
    delay(500);
    reverse();
    delay(500);
    stopAll();
}

void angry(){
    leftForward();
    rightReverse();
    delay(500);
    leftReverse();
    rightForward();
    delay(1000);
    leftForward();
    rightReverse();
    delay(500);
    stopAll();
}

void scared(){
    forward();
}
void disgusted(){}

void forward(){
    leftForward();
    rightForward();
}
void reverse(){
    leftReverse();
    rightReverse();
}
void stopAll(){
    leftStop();
    rightStop();
}
void leftStop(){
    digitalWrite(N1, LOW);
    digitalWrite(N2, LOW);
    Serial.println("Stop left");
}
void rightStop(){
    digitalWrite(N3, LOW);
    digitalWrite(N4, LOW);
    Serial.println("Stop right");
}
void leftForward(){
    digitalWrite(N1, HIGH);
    digitalWrite(N2, LOW);
    Serial.println("Forward left");
}
void rightForward(){
    digitalWrite(N3, HIGH);
    digitalWrite(N4, LOW);
    Serial.println("Forward right");
}
void leftReverse(){
    digitalWrite(N1, LOW);
    digitalWrite(N2, HIGH);
    Serial.println("Reverse left");
}
void rightReverse(){
    digitalWrite(N3, LOW);
    digitalWrite(N4, HIGH);
    Serial.println("Reverse right");
}

void setup(){
    pinMode(N1, OUTPUT);
    pinMode(N2, OUTPUT);
    pinMode(N3, OUTPUT);
    pinMode(N4, OUTPUT);

    Serial.begin(9600);
    Serial.println("I am ready");
}

void loop(){
    char in = '9';
    if (Serial.available() > 0){
        in = Serial.read();
        Serial.print("Recieved ");
        Serial.println(in); 
    }
    switch (in){
        case '0':
        neutral();
        break;
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
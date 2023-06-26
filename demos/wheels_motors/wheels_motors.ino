int STBY = 10;

// Motor A
int PWMA = 3; // Speed control
int AIN1 = 9; // Direction
int AIN2 = 8; // Direction

// Motor B
int PWMB = 5;  // Speed control
int BIN1 = 11; // Direction
int BIN2 = 12; // Direction

void move(int motor, int speed, int direction){
    // Move specific motor at speed and direction
    // motor: 0 for B 1 for A
    // speed: 0 is off, and 255 is full speed
    // direction: 0 clockwise, 1 counter-clockwise

    digitalWrite(STBY, HIGH); 
    boolean inPin1 = LOW;
    boolean inPin2 = HIGH;

    if (direction == 1){
        inPin1 = HIGH;
        inPin2 = LOW;
    }

    if (motor == 1){
        digitalWrite(AIN1, inPin1);
        digitalWrite(AIN2, inPin2);
        analogWrite(PWMA, speed);
    }
    else{
        digitalWrite(BIN1, inPin1);
        digitalWrite(BIN2, inPin2);
        analogWrite(PWMB, speed);
    }
}

void stop(){
    digitalWrite(STBY, LOW);
}

void setup(){
    pinMode(STBY, OUTPUT);

    pinMode(PWMA, OUTPUT);
    pinMode(AIN1, OUTPUT);
    pinMode(AIN2, OUTPUT);

    pinMode(PWMB, OUTPUT);
    pinMode(BIN1, OUTPUT);
    pinMode(BIN2, OUTPUT);
}

void loop(){
    move(1, 100, 1); // motor 1/2, full speed, left/right
    move(2, 100, 1);

    delay(1000); 
    stop();      
    delay(250);  

    move(1, 100, 0); 
    move(2, 100, 0); 

    delay(1000);
    stop();
    delay(100000);
}
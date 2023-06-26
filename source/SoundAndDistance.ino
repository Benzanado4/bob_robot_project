#define trig 9
#define echo 8

#define mic 2

String mood = "sad";

long dist = 0;
long loudStart = 0, loudFor = 0;
boolean lastLoud = false, loudBang = false, longSound = false;

void detectSound(){
    /*Detects every 100ms sounds, if it detects for more than 3 times some sound it will be disgusted,
    if it detects between 1 and 3 it will be scared, otherwise nothing.*/
    int counter = 0;
    boolean val[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (int n = 0; n < 10; n++){
        val[n] = digitalRead(mic);
        if (val[n]==1)
            counter++;
        delay(100);
    }
    if (counter==0){
        loudBang = false;
        longSound = false;
    } else if (counter<3){
        loudBang = true;
        longSound = false;
    } else {
        loudBang = false;
        longSound = true;
    }
}

long getRange(int t, int e){
    digitalWrite(t, LOW);
    delayMicroseconds(5);
    digitalWrite(t, HIGH);
    delayMicroseconds(5);
    digitalWrite(t, LOW);

    long duration = pulseIn(e, HIGH);
    delay(5);

    return duration * 0.034 / 2;
}

void setup(){
    Serial.begin(9600);
    pinMode(trig, OUTPUT);
    pinMode(echo, INPUT);
    pinMode(mic, INPUT);
}

void loop(){
    dist = getRange(trig, echo);
    detectSound();

    if (loudBang){
        mood = "scared";
    } else if (longSound){
        mood = "disgusted";
    } else {
        if (dist > 200){
            mood = "sad";
        } else if (dist > 100){
            mood = "happy";
        } else {
            mood = "angry";
        }
    }
    Serial.print("I am ");
    Serial.println(mood);
    delay(1000);
}


int  trig = 12;
int  echo = 11;
long lecture_echo;
int DELAY_VIT_CALCULATION = 500;
int distprec = 0;
int dist     = 0;
int vit      = 0;
int count    = 0;

void setup(){
    pinMode(trig, OUTPUT);
    digitalWrite(trig, LOW);
    pinMode(echo, INPUT);
    Serial.begin(9600);
}

void loop(){
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    lecture_echo = pulseIn(echo, HIGH);
    distprec =
        lecture_echo / 58; 
    Serial.print("distprec :");
    Serial.print(distprec);
    delay(DELAY_VIT_CALCULATION);
    if (distprec < 500){
        digitalWrite(trig, HIGH);
        delayMicroseconds(10);
        digitalWrite(trig, LOW);
        lecture_echo = pulseIn(echo, HIGH); 
        dist         = lecture_echo
               / 58; 
        Serial.print("    dist :");
        Serial.println(dist);
        if ((dist < distprec) && (abs(distprec - dist) < 200)){
            vit = (distprec - dist) / 0.2; 
            Serial.print("Vitesse en cm/s : ");
            Serial.println(vit);
            if (vit >= 80){
                Serial.print("Haa");
                while (count < 200){
                    while (count < 100){
                        Serial.print("a");
                        count++;
                        delay(25);
                    }
                    Serial.println("a");
                    while (count < 200)
                    {
                        Serial.print("a");
                        count++;
                        delay(25);
                    }
                }
                Serial.println(" !!!");
                Serial.println("");
                count = 0;
            }
            else{
                Serial.println("Sono felice");
                Serial.println(" ");
            }
        }
    }
}

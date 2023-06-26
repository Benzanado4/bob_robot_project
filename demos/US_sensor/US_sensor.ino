int  trig = 12;
int  echo = 11;
long lecture_echo;


int DELAY_VIT_CALCULATION = 200;
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
    distprec = dist;
                    
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    lecture_echo = pulseIn(echo, HIGH);
    dist =
        lecture_echo / 58; 

    if ((abs(distprec - dist) < 200) && (dist < 2000)){
        Serial.print("Distance en cm : ");
        Serial.println(dist);
        vit =
            (distprec - dist) / (DELAY_VIT_CALCULATION / 1000); 
        Serial.print("Vitesse en cm/s : ");
        Serial.println(vit);
        if (vit >= 50){
            Serial.print("Haa");
            while (count < 200){
                while (count < 100){
                    Serial.print("a");
                    count++;
                    delay(25);
                }
                Serial.println("a");
                while (count < 200){
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
    delay(DELAY_VIT_CALCULATION);
}

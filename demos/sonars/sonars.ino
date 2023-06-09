#include <NewPing.h>

#define TRIGGER_PIN 48
#define ECHO_PIN 50 
#define MAX_DISTANCE 400

NewPing sonar(TRIGGER_PIN,
              ECHO_PIN,
              MAX_DISTANCE);

void setup(){
    Serial.begin(115200);
}

void loop(){
    delay(50);
    unsigned int uS = sonar.ping_cm();
    Serial.print(uS);
    Serial.println("cm");
}

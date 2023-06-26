#include <NewPing.h>

#define FRONT_TRIGGER_PIN 46
#define FRONT_ECHO_PIN 44
#define REAR_TRIGGER_PIN 48
#define REAR_ECHO_PIN 50
#define MAX_DISTANCE 400
#define MSRMNT_TIME_OUT 50
#define DISTANCE_VERY_CLOSE 10
#define DISTANCE_NEAR 60
#define DISTANCE_MEDIUM 160
#define DISTANCE_FAR 250

NewPing f_sonar(FRONT_TRIGGER_PIN, FRONT_ECHO_PIN, MAX_DISTANCE); 
NewPing r_sonar(REAR_TRIGGER_PIN, REAR_ECHO_PIN, MAX_DISTANCE);
enum Sonar_enum{SONAR_NEAR, SONAR_MEDIUM, SONAR_FAR, SONAR_COLLISION};


// #### TIMERS ####
unsigned long front_last_measurement_time; 
unsigned long rear_last_measurement_time; 

 
byte front_sonar(){
    if (millis() - front_last_measurement_time >= MSRMNT_TIME_OUT){
        unsigned int distance = f_sonar.ping_cm();
        front_last_measurement_time = millis();

        if(distance >= DISTANCE_FAR || distance == 0){
            return SONAR_FAR;
        }else if(distance <= DISTANCE_MEDIUM && distance > DISTANCE_NEAR){
            return SONAR_MEDIUM; 
        }else if(distance <= DISTANCE_NEAR && distance > DISTANCE_VERY_CLOSE){
            return SONAR_NEAR;
        }else if(distance <= DISTANCE_VERY_CLOSE){
            return SONAR_COLLISION;
        }
    }
}

byte rear_sonar(){
    if (millis() - rear_last_measurement_time >= MSRMNT_TIME_OUT){
        unsigned int distance = r_sonar.ping_cm();
        rear_last_measurement_time = millis();
        if(distance >= DISTANCE_FAR || distance == 0){
            return SONAR_FAR;
        }else if(distance <= DISTANCE_MEDIUM && distance > DISTANCE_NEAR){
            return SONAR_MEDIUM; 
        }else if(distance <= DISTANCE_NEAR && distance > DISTANCE_VERY_CLOSE){
            return SONAR_NEAR;
        }else if(distance <= DISTANCE_VERY_CLOSE){
            return SONAR_COLLISION;
        }
    }
}

void setupSonars(){
    front_last_measurement_time = millis();
    rear_last_measurement_time = millis();
}


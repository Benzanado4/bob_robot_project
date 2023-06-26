// #### LIBRARIES ####
#include <SparkFun_TB6612.h>
// #### DEFINITIONS ####
#define LK_TIME_OUT 8000 
#define WHE_SPOT_ROT_TIME_OUT 1000
#define SPOT_ROT_SPEED 200
#define RAND_SAD_TIME_OUT 12000 
#define RAND_SAD_PROB 50 
#define WHE_SAD_TIME_OUT 1000 
#define RAND_SAD_SPEED 150  
#define ANGER_TIME_OUT 6700 
#define ANGER_SPEED_BACK 150
#define ANGER_SPEED_FRONT 240
#define ANGER_PROB 9 
#define FEAR_TIME_OUT 4000 
#define WHE_FEAR_TIME_OUT 500 
#define FEAR_SPEED 255
#define FEAR_PROB 4 
#define DISGUST_TIME_OUT 4000 
#define WHE_DISGUST_TIME_OUT 500 
#define EXC_TIME_OUT 4500 
#define EXCITEMENT_SPEED 200
#define WHE_EXC_TIME_OUT 1000 
#define BETWEEN_EXC_TIME_OUT 30000 
#define JOY_TIME_OUT 5000
#define JOY_PROB 6
#define WHE_JOY_TIME_OUT 500
#define JOY_SPEED 200
#define WAIT_TIME_OUT 15000 
#define GIGGLE_TIME_OUT 5000
#define WHE_GIGGLE_TIME_OUT 1000
#define FRIGHT_TIME_OUT 5000
#define SERVO_CLOSED_DEGREE 85
#define SERVO_OPEN_DEGREE 30

enum State_enum {LOOK_AROUND, SPOT_ROTATION, RANDOM_SAD, JOY_STATE, DISGUST_STATE, ANGRY_STATE, EXCITEMENT_STATE, WAIT_INTERACTION, 
                 FRONT_COLLISION_STATE, REAR_COLLISION_STATE, FEAR_STATE, GIGGLE_STATE, FRIGHT_STATE, GO_AWAY}; // all possible states of the robot
byte current_state;
bool first_time_state;

unsigned long starting_time_state; 
unsigned long last_excitement;
unsigned long timer_state1;
unsigned long timer_state2;
unsigned long timer_state3;
unsigned long timer_state4;
unsigned long timer_state5;
unsigned long timer_state6;
unsigned long timer_state7;
bool  case_state1;
bool  case_state2;
bool  case_state3;
bool  case_state4;
bool  case_state5;
bool  case_state6;
bool  case_state7;

// #### WHEELS MOTORS ####
// Pins for all inputs, keep in mind the PWM defines must be on PWM pins
#define AIN1 34
#define BIN1 38
#define AIN2 32
#define BIN2 40
#define PWMA 2
#define PWMB 3
#define STBY 3
// line up with function names like forward.  Value can be 1 or -1
const int offsetA = 1;
const int offsetB = 1;

// Initializing motors
Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);
// #### STATE MACHINE ####
// state machine that controls the robot
void stateMachine(){
    switch (current_state){
        case LOOK_AROUND:
            if (first_time_state){
                setAnimation(LOOKING);
                first_time_state = false;

                 #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("LOOK AROUND");
                #endif
            }
            else if (millis() - starting_time_state > LK_TIME_OUT){
                setState(SPOT_ROTATION);               
            }
            else {
                byte sensors = front_sonar();

                if(sensors == SONAR_NEAR){
                    if(random(10) >= (10 - JOY_PROB)){
                        setState(JOY_STATE);
                    }
                    else {
                        setState(DISGUST_STATE);
                    }
                    #if defined(DEVMODE)
                        Serial.print("Sonar State: ");
                        Serial.println("FRONT SONAR NEAR");
                    #endif             
                }
                else if(sensors == SONAR_MEDIUM){
                    if (millis() - last_excitement >= BETWEEN_EXC_TIME_OUT){
                        last_excitement = millis();
                        setState(EXCITEMENT_STATE);

                        #if defined(DEVMODE)
                            Serial.print("Sonar State: ");
                            Serial.println("FRONT SONAR MEDIUM");
                        #endif
                    } 
                }
                else if(sensors == SONAR_FAR){
                    #if defined(DEVMODE)
                        Serial.print("State: ");
                        Serial.println("FRONT SONAR FAR");
                    #endif
                    if(random(10000) >= (10000 - RAND_SAD_PROB)){
                        setState(RANDOM_SAD);
                    }
                }
                else if(thermosensor()){
                    setState(FRIGHT_STATE);

                    #if defined(DEVMODE)
                        Serial.println("Thermosensor HAND DETECTED");
                    #endif
                 }     
            }
            break;
        case SPOT_ROTATION:
            if(first_time_state){
                first_time_state = false;
                timer_state1 = millis() - WHE_SPOT_ROT_TIME_OUT;
                case_state1 = true;
                setAnimation(EXCITEMENT);

                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("SPOT ROTATION");
                #endif 
            }
            else {
                    if(millis() - timer_state1 >= WHE_SPOT_ROT_TIME_OUT && case_state1){
                        left(motor1, motor2, SPOT_ROT_SPEED);  
                        case_state1 = false;
                        case_state2 = true;
                        timer_state2 = millis();
                    }
                    else if (millis() - timer_state2 >= WHE_SPOT_ROT_TIME_OUT && case_state2){
                        right(motor1, motor2, SPOT_ROT_SPEED);
                        case_state2 = false;
                        case_state3 = true;
                        timer_state3 = millis();
                    }
                    else if (millis() - timer_state3 >= WHE_SPOT_ROT_TIME_OUT && case_state3){
                        left(motor1, motor2, SPOT_ROT_SPEED);
                        case_state3 = false;
                        case_state4 = true;
                        timer_state4 = millis();
                    }
                    else if (millis() - timer_state4 >= WHE_SPOT_ROT_TIME_OUT && case_state4){
                        right(motor1, motor2, SPOT_ROT_SPEED);
                        case_state4 = false;
                        case_state5 = true;
                        timer_state5 = millis();
                    }
                    else if (millis() - timer_state5 >= WHE_SPOT_ROT_TIME_OUT && case_state5){
                        forward(motor1, motor2, 150);
                        case_state5 = false;
                        case_state6 = true;
                        timer_state6 = millis();
                    }
                    else if (millis() - timer_state6 >= WHE_SPOT_ROT_TIME_OUT && case_state6){
                        back(motor1, motor2, 150);
                        case_state6 = false;
                        case_state7 = true;
                        timer_state7 = millis();
                    }  
                    else if(millis() - timer_state7 >= WHE_SPOT_ROT_TIME_OUT && case_state7){
                         brake(motor1, motor2);
                         setState(LOOK_AROUND);        
                    }
            }                  
            break;
        case EXCITEMENT_STATE: 
            if(first_time_state){
                first_time_state = false; 
                setAnimation(EXCITEMENT);  
                timer_state1 = millis() - WHE_EXC_TIME_OUT;
                case_state1 = true;

                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("EXCITEMENT");
                #endif
            }else if(millis() - starting_time_state >= EXC_TIME_OUT){
                brake(motor1, motor2);  
                setState(LOOK_AROUND);
            } 
            else {
                if(millis() - timer_state1 >= WHE_EXC_TIME_OUT && case_state1){
                    left(motor1, motor2, EXCITEMENT_SPEED); 
                    case_state1 = false;
                    case_state2 = true;
                    timer_state2 = millis();
                }
                else if (millis() - timer_state2 >= WHE_EXC_TIME_OUT && case_state2){
                    right(motor1, motor2, EXCITEMENT_SPEED);
                    case_state2 = false;
                    case_state1 = true;
                    timer_state1 = millis();
                }
            }
            break;     
        case RANDOM_SAD:
            if (first_time_state){
                first_time_state = false;  
                setAnimation(SADNESS);
                timer_state1 = millis() - WHE_SAD_TIME_OUT;
                case_state1 = true;
            
                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("RANDOM SAD");
                #endif
            } 
            else if (millis() - starting_time_state >= RAND_SAD_TIME_OUT){
                brake(motor1, motor2);  
                delay(1000); 
                setState(LOOK_AROUND); 
            }
            else if (front_sonar() == SONAR_COLLISION){
                brake(motor1, motor2);
                setState(FRONT_COLLISION_STATE);
            }
            else {
                if(millis() - timer_state1 >= WHE_SAD_TIME_OUT && case_state1){
                    left(motor1, motor2, RAND_SAD_SPEED); 
                    case_state1 = false;
                    case_state2 = true;
                    timer_state2 = millis();
                }
                else if (millis() - timer_state2 >= WHE_SAD_TIME_OUT && case_state2){
                    forward(motor1, motor2, RAND_SAD_SPEED);
                    case_state2 = false;
                    case_state3 = true;
                    timer_state3 = millis();
                }
                else if (millis() - timer_state3 >= WHE_SAD_TIME_OUT && case_state3){
                    right(motor1, motor2, RAND_SAD_SPEED);
                    case_state3 = false;
                    case_state4 = true;
                    timer_state4 = millis();
                }
                else if (millis() - timer_state4 >= WHE_SAD_TIME_OUT && case_state4){
                    forward(motor1, motor2, RAND_SAD_SPEED);
                    case_state4 = false;
                    case_state1 = true;
                    timer_state1 = millis();
                }
            }  
            break;
        case JOY_STATE:
            if(first_time_state){
                first_time_state = false;
                setAnimation(JOY);
                timer_state1 = millis() - WHE_JOY_TIME_OUT;
                case_state1 = true;
                
                #if defined(DEVMODE)
                    Serial.print("State: ");
                    Serial.println("RANDOM ANIMATION JOY");
                #endif       
            }
            else if (millis() - starting_time_state >= JOY_TIME_OUT){
                brake(motor1, motor2);
                moveServo(SERVO_OPEN_DEGREE);
                setState(WAIT_INTERACTION);
            }
            else if (front_sonar() == SONAR_COLLISION){
                brake(motor1, motor2);
                setState(FRONT_COLLISION_STATE);
            }
            else{
                if(millis() - timer_state1 >= WHE_JOY_TIME_OUT && case_state1){
                    left(motor1, motor2, JOY_SPEED); 
                    case_state1 = false;
                    case_state2 = true;
                    timer_state2 = millis();
                }
                else if (millis() - timer_state2 >= WHE_JOY_TIME_OUT && case_state2){
                    right(motor1, motor2, JOY_SPEED);
                    case_state2 = false;
                    case_state1 = true;
                    timer_state1 = millis();
                }
            }
        break;
    case DISGUST_STATE:
        if(first_time_state){
            first_time_state= false; 
            setAnimation(DISGUST);
            timer_state1 = millis() - WHE_DISGUST_TIME_OUT;
            case_state1 = true;
            
            #if defined(DEVMODE)
                Serial.print("State: ");
                Serial.println("RANDOM ANIMATION DISGUST");
            #endif
         }else if (millis() - starting_time_state >= DISGUST_TIME_OUT){
                brake(motor1, motor2);
                moveServo(85);
                setState(GO_AWAY);
         }
         else if (rear_sonar() == SONAR_COLLISION){
                brake(motor1, motor2);
                setState(REAR_COLLISION_STATE);
         }
         else{
            if(millis() - timer_state1 >= 1000 && case_state1){
                left(motor1, motor2, 140); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();
             }
             else if (millis() - timer_state2 >= WHE_DISGUST_TIME_OUT && case_state2){
                right(motor1, motor2, 140);
                case_state2 = false;
                case_state3 = true;
                timer_state3 = millis();
              }
              else if (millis() - timer_state3 >= WHE_DISGUST_TIME_OUT && case_state3){
                back(motor1, motor2, 140);
                case_state3 = false;
                case_state1 = true;
                timer_state1 = millis();
              }
          }            
        break;
    case FRONT_COLLISION_STATE: 
        {
        delay(500);
        back(motor1, motor2, 160);
        delay(1500); 
        setState(LOOK_AROUND);
        }
        break;
    case REAR_COLLISION_STATE: 
        {

        delay(500);
        forward(motor1, motor2, 160);
        delay(1500); 
        setState(LOOK_AROUND);

        }
        break;
    case WAIT_INTERACTION: 
       if(first_time_state){
                first_time_state = false;
                setAnimation(LOOK_AROUND);
                                
                #if defined(DEVMODE)
                    Serial.println("State: WAIT INTERACTION");
                #endif       
        }
        else if (millis() - starting_time_state >= WAIT_TIME_OUT){
                setState(LOOK_AROUND);   
        }
        else if (thermosensor()){
            int probability = random(15);
            
            if(probability <= FEAR_PROB){
                setState(FEAR_STATE);
            }
            else if(probability <= ANGER_PROB && probability > FEAR_PROB){
                setState(ANGRY_STATE);
            }
            else{
              setState(GIGGLE_STATE);
            }
         }
        break;
    case ANGRY_STATE:
      if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - 400;
            case_state1 = true;
            setAnimation(ANGER);
                                
            #if defined(DEVMODE)
                Serial.println("State: ANGRY STATE");
            #endif       
       }
       else if (millis() - starting_time_state >= ANGER_TIME_OUT){
            brake(motor1, motor2);
            setState(LOOK_AROUND);   
       }
       else if (front_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(FRONT_COLLISION_STATE);
       }
       else if (rear_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(REAR_COLLISION_STATE);
       }
       else {
            if(millis() - timer_state1 >= 1000 && case_state1){
                back(motor1, motor2, ANGER_SPEED_BACK); 
                moveServo(60);
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();
            }
            else if (millis() - timer_state2 >= 600 && case_state2){
                forward(motor1, motor2, ANGER_SPEED_FRONT); 
                moveServo(SERVO_OPEN_DEGREE);
                case_state2 = false;
                case_state1 = true;
                timer_state1 = millis();
            }
        }      
        break;
    case FEAR_STATE:
        if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - WHE_FEAR_TIME_OUT;
            case_state1 = true;
            setAnimation(FEAR); 

            #if defined(DEVMODE)
                Serial.println("State: FEAR STATE");
            #endif
        }else if(millis() - starting_time_state > FEAR_TIME_OUT){
            brake(motor1,motor2);
            moveServo(SERVO_CLOSED_DEGREE);
            delay(1000);
            setState(LOOK_AROUND);
        }
        else if (rear_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(REAR_COLLISION_STATE);
        }                        
        else {
          if(millis() - timer_state1 >= WHE_FEAR_TIME_OUT && case_state1){
                back(motor1, motor2, 255); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= 3000 && case_state2){
                left(motor1, motor2, 255);
                case_state2 = false;
            }
        }
        break;
     case GIGGLE_STATE: 
       if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - WHE_GIGGLE_TIME_OUT;
            case_state1 = true;
            
            setAnimation(GIGGLE); 

            #if defined(DEVMODE)
                Serial.println("State: GIGGLE STATE");
            #endif
        }else if(millis() - starting_time_state > GIGGLE_TIME_OUT){
            playAudio(GOOD_BYE);
            moveServo(75);
            setState(GO_AWAY);
        }
        else {
            if(millis() - timer_state1 >= WHE_GIGGLE_TIME_OUT && case_state1){
                left(motor1, motor2, 200); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= WHE_GIGGLE_TIME_OUT && case_state2){
                right(motor1, motor2, 200);
                case_state2 = false;
                case_state1 = true;
                timer_state1 = millis();
            } 
        }
        break;
    case GO_AWAY:
        if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - 500;
            case_state1 = true;

            #if defined(DEVMODE)
                Serial.println("State: GO AWAY");
            #endif
        }
        else if (millis() - starting_time_state > 3000){
             setState(LOOK_AROUND);
        }
        else if (front_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(FRONT_COLLISION_STATE);
        }
        else {
            if(millis() - timer_state1 >= 500 && case_state1){
                right(motor1, motor2, 230);
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= 1000 && case_state2){
                forward(motor1, motor2, 230);  
                case_state2 = false;
                case_state3 = true;
                timer_state3 = millis();   
            }
            else if(millis() - timer_state3 >= 2000 && case_state3){
                brake(motor1, motor2);
                case_state3 = false;
            }    
         } 
        break;
    case FRIGHT_STATE:
        if(first_time_state){
            first_time_state = false;
            timer_state1 = millis() - 3000;
            case_state1 = true;
            
            setAnimation(FEAR); 

            #if defined(DEVMODE)
                Serial.println("State: FRIGHT STATE");
            #endif
        }else if(millis() - starting_time_state > FRIGHT_TIME_OUT){
            brake(motor1,motor2);
            moveServo(SERVO_CLOSED_DEGREE);
            delay(1000);
            setState(LOOK_AROUND);
        }
        else if (front_sonar() == SONAR_COLLISION){
            brake(motor1, motor2);
            setState(FRONT_COLLISION_STATE);
        }
        else {
            if(millis() - timer_state1 >= 500 && case_state1){
                forward(motor1, motor2, 240); 
                case_state1 = false;
                case_state2 = true;
                timer_state2 = millis();                  
            }
            else if (millis() - timer_state2 >= 3000 && case_state2){
                left(motor1, motor2, 255);
                case_state2 = false;
            }
        }
        break;
    default: 
        break;
    }
}

void setState(byte state){
    current_state       = state;
    first_time_state = true;
    starting_time_state = millis();
    case_state1 = false;
    case_state2 = false;
    case_state3 = false;
    case_state4 = false;
    case_state5 = false;
    case_state6 = false;
    case_state7 = false;
}

void setupState(){
    starting_time_state = millis();
    first_time_state = true;
    current_state  = LOOK_AROUND;
    last_excitement = millis();
}
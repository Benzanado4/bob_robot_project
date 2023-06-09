#include <Adafruit_NeoPixel.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_GFX.h>

#define PIN 52
#define BRIGHTNESS 5
#define LK_EYE_TIME_OUT 500 
#define EXC_EYE_TIME_OUT 250  

int DELAY_EYE = 30; 

byte current_emotion; 
byte previous_emotion;

// #### TIME ####
unsigned long timer_eye1;
unsigned long timer_eye2;
unsigned long timer_eye3;
unsigned long timer_eye4;
unsigned long timer_eye5;
unsigned long timer_eye6;
unsigned long timer_eye7;
bool  case_eye1;
bool  case_eye2;
bool  case_eye3;
bool  case_eye4;
bool  case_eye5;
bool  case_eye6;
bool  case_eye7;

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN, NEO_MATRIX_TOP + NEO_MATRIX_RIGHT + NEO_MATRIX_ROWS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);

struct RGB{
    byte r;
    byte g;
    byte b;
};
 
RGB vanilla = { 225, 246, 201 }; 

// angry
RGB red1 = { 255, 201, 177 };
RGB red2 = { 255, 145, 133 };
RGB red3 = { 255, 112, 97 };
RGB red4 = { 254, 27, 0 }; 
//joy
RGB yellow1= { 255, 240, 183 };
RGB yellow2= { 255, 236, 143 };
RGB yellow3= { 255, 231, 113 };
RGB yellow4= { 255, 215, 0 }; 
//giggle
RGB orange1= { 255, 240, 183 };
RGB orange2= { 255, 220, 143 };
RGB orange3= { 255, 180, 113 };
RGB orange4= { 255, 140, 0 }; 
//sadness
RGB blue1 = { 180, 254, 198 };
RGB blue2 = { 137, 224, 255 };
RGB blue3 = { 91, 212, 255 };
RGB blue4 = { 0, 176, 240 }; 
//disgust
RGB green1 = {189, 224, 128};
RGB green2 = {180, 214, 86 };
RGB green3 = {159, 198 , 48 };
RGB green4 = {112, 141, 35 }; 
//fear
RGB purple1 = { 221, 175, 255 };
RGB purple2 = { 165, 45, 255 };
RGB purple3 = { 136, 0, 238 };
RGB purple4 = { 75, 0, 130 }; 

RGB off = { 0, 0, 0 };

bool const angry3[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 0, 0, 0, 0, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };
            
bool const angry4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 0, 0, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

bool const happy1[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };
            
bool const happy2 [8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };
                    
bool const happy3 [8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 0, 0, 0, 0, 0, 0, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };   
                  
bool const happy4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 0, 0, 0, 0, 1, 1},
             {1, 0, 0, 0, 0, 0, 0, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

bool const sadness1[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };

bool const sadness2[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };
bool const sadness3[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 0, 0, 0, 0, 0, 0, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };
            
bool const sadness4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 0, 0, 0, 0, 0, 0, 1},
             {1, 1, 0, 0, 0, 0, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
            };

bool const fear3[8][8] = {
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 0, 0, 0, 0, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 0, 0, 0, 0, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

bool const fear4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 0, 0, 0, 0, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 0, 0, 0, 0, 1, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };


bool const disgust4[8][8] = {        
             {0, 1, 0, 0, 0, 0, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {0, 1, 0, 0, 0, 0, 1, 0}
            };
            
bool const disgust3[8][8] = {        
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 0, 0, 1, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };
            
bool const disgust2[8][8] = {        
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 1, 0, 0, 1, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
            };
            
bool const disgust1[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 1, 1, 0, 0, 0},
             {0, 0, 0, 1, 1, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

bool const neutral1[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };

bool const neutral2[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

bool const neutral3[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 0, 0, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

bool const neutral4[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };  

    
bool const left1[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 0, 0, 1, 1, 1, 1},
             {1, 1, 0, 0, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };

bool const left2[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 0, 0, 1, 1, 1, 1, 1},
             {1, 0, 0, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };

bool const right1[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 0, 0, 1, 1},
             {1, 1, 1, 1, 0, 0, 1, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };

bool const right2[8][8] = {  
             {0, 0, 1, 1, 1, 1, 0, 0},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {1, 1, 1, 1, 1, 0, 0, 1},
             {1, 1, 1, 1, 1, 0, 0, 1},
             {1, 1, 1, 1, 1, 1, 1, 1},
             {0, 1, 1, 1, 1, 1, 1, 0},
             {0, 0, 1, 1, 1, 1, 0, 0}
            };       
   
bool const turned_off[8][8] = {  
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0},
             {0, 0, 0, 0, 0, 0, 0, 0}
            };

enum Eye_enum { LEFT_EYE, NEUTRAL_FROM_LEFT, RIGHT_EYE, NEUTRAL_FROM_RIGHT,
                EXCITEMENT_EYE,
                LOOKING_FROM_JOY, LOOKING_FROM_SADNESS, LOOKING_FROM_ANGER, LOOKING_FROM_FEAR, LOOKING_FROM_DISGUST, LOOKING_FROM_GIGGLE, 
                JOY_EYE, SADNESS_EYE, ANGER_EYE, FEAR_EYE, DISGUST_EYE, GIGGLE_EYE};

bool first_time_eye;

//Define the sequence of eye position for each emotion
void eyesInlight(byte eye)
{  
   switch(eye){
        case LEFT_EYE:
            drawEye(left1, vanilla); 
            delay(DELAY_EYE);
            drawEye(left2, vanilla);
            break;
        case NEUTRAL_FROM_LEFT:
            drawEye(left1, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case RIGHT_EYE:
            drawEye(right1, vanilla);
            delay(DELAY_EYE);
            drawEye(right2, vanilla);
            break;
        case NEUTRAL_FROM_RIGHT:
            drawEye(right1, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case SADNESS_EYE:
            drawEye(sadness1, blue1);
            delay(DELAY_EYE);
            drawEye(sadness2, blue2);
            delay(DELAY_EYE);
            drawEye(sadness3, blue3);
            delay(DELAY_EYE);
            drawEye(sadness4, blue4);
            break;
        case LOOKING_FROM_SADNESS:
            drawEye(sadness3, blue3);
            delay(DELAY_EYE);
            drawEye(sadness2, blue2);
            delay(DELAY_EYE);
            drawEye(sadness1, blue1);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break; 
        case EXCITEMENT_EYE:
            drawEye(neutral1, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral2, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral3, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral4, vanilla);
            delay(DELAY_EYE);
            drawEye(turned_off, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral4, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral3, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral2, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case JOY_EYE:
            drawEye(happy1, yellow1);
            delay(DELAY_EYE);
            drawEye(happy2, yellow2);
            delay(DELAY_EYE);
            drawEye(happy3, yellow3);
            delay(DELAY_EYE);
            drawEye(happy4, yellow4);
            break;
        case LOOKING_FROM_JOY:
            drawEye(happy3, yellow3);
            delay(DELAY_EYE);
            drawEye(happy2, yellow2);
            delay(DELAY_EYE);
            drawEye(happy1, yellow1);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case GIGGLE_EYE:
            drawEye(happy1, orange1);
            delay(DELAY_EYE);
            drawEye(happy2, orange2);
            delay(DELAY_EYE);
            drawEye(happy3, orange3);
            delay(DELAY_EYE);
            drawEye(happy4, orange4);
            break;
        case LOOKING_FROM_GIGGLE:
            drawEye(happy3, orange3);
            delay(DELAY_EYE);
            drawEye(happy2, orange2);
            delay(DELAY_EYE);
            drawEye(happy1, orange1);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case ANGER_EYE:
            drawEye(neutral1, vanilla);
            delay(DELAY_EYE);
            drawEye(sadness1, red1);
            delay(DELAY_EYE);
            drawEye(sadness2, red2);
            delay(DELAY_EYE);
            drawEye(angry3, red3);
            delay(DELAY_EYE);
            drawEye(angry4, red4);
            break;
        case LOOKING_FROM_ANGER:
            drawEye(angry3, red3);
            delay(DELAY_EYE);
            drawEye(sadness2, red2);
            delay(DELAY_EYE);
            drawEye(sadness1, red1);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case FEAR_EYE:
           drawEye(neutral1, vanilla);
            delay(DELAY_EYE);
            drawEye(neutral2, purple1);
            delay(DELAY_EYE);
            drawEye(neutral3, purple2);
            delay(DELAY_EYE);
            drawEye(fear3, purple3);
            delay(DELAY_EYE);
            drawEye(fear4, purple4);
            break; 
        case LOOKING_FROM_FEAR:
            drawEye(fear3, purple3);
            delay(DELAY_EYE);
            drawEye(neutral3, purple2);
            delay(DELAY_EYE);
            drawEye(neutral2, purple1);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        case DISGUST_EYE:
            drawEye(neutral1, vanilla);
            delay(DELAY_EYE); 
            drawEye(disgust1,green1);
            delay(DELAY_EYE);
            drawEye(disgust2,green2);
            delay(DELAY_EYE);
            drawEye(disgust3,green3);
            delay(DELAY_EYE);
            drawEye(disgust4,green4);
            break; 
        case LOOKING_FROM_DISGUST:
            drawEye(disgust3, green3);
            delay(DELAY_EYE);
            drawEye(disgust2, green2);
            delay(DELAY_EYE);
            drawEye(disgust1, green1);
            delay(DELAY_EYE);
            drawEye(neutral1, vanilla);
            break;
        default:
            break;        
    }
}    

void setupMatrix(){
    matrix.begin();
    matrix.setBrightness(BRIGHTNESS);
    current_emotion = LOOKING;
    previous_emotion = LOOKING;
}


void setEye(byte emotion){
    current_emotion = emotion;
    first_time_eye = true;
    case_eye1 = false;
    case_eye2 = false;
    case_eye3 = false;
    case_eye4 = false;
    case_eye5 = false;
    case_eye6 = false;
    case_eye7 = false;
}

void showEyeAnimation(){
    switch (current_emotion){
        case LOOKING:
            if(first_time_eye){
                switch(previous_emotion){
                    case SADNESS:
                        eyesInlight(LOOKING_FROM_SADNESS);
                        break;
                    case JOY:
                        eyesInlight(LOOKING_FROM_JOY);
                        break;
                    case GIGGLE:
                        eyesInlight(LOOKING_FROM_GIGGLE);
                        break;
                    case ANGER:
                        eyesInlight(LOOKING_FROM_ANGER);
                        break;
                    case DISGUST:
                        eyesInlight(LOOKING_FROM_DISGUST);
                        break;
                    case FEAR:
                        eyesInlight(LOOKING_FROM_FEAR);
                        break;
                    default:
                        break;
                }
                previous_emotion = LOOKING;
                first_time_eye = false; 
                case_eye1 = true; 
                timer_eye1 = millis() - LK_EYE_TIME_OUT;
            }
            else {
                if(millis() - timer_eye1 >= LK_EYE_TIME_OUT && case_eye1){
                    eyesInlight(LEFT_EYE);
                    case_eye1 = false;
                    case_eye2 = true;
                    timer_eye2 = millis();
                }
                else if (millis() - timer_eye2 >= LK_EYE_TIME_OUT && case_eye2){
                    //the eye stays left
                    case_eye2 = false;
                    case_eye3 = true;
                    timer_eye3 = millis();
                }
                else if (millis() - timer_eye3 >= LK_EYE_TIME_OUT && case_eye3){
                    eyesInlight(NEUTRAL_FROM_LEFT);
                    case_eye3 = false;
                    case_eye4 = true;
                    timer_eye4 = millis();
                }
                else if (millis() - timer_eye4 >= LK_EYE_TIME_OUT && case_eye4){
                    //the eye stays neutral
                    case_eye4 = false;
                    case_eye5 = true;
                    timer_eye5 = millis();
                }
                else if (millis() - timer_eye5 >= LK_EYE_TIME_OUT && case_eye5){
                    eyesInlight(RIGHT_EYE);
                    case_eye5 = false;
                    case_eye6 = true;
                    timer_eye6 = millis();
                }
                else if (millis() - timer_eye6 >= LK_EYE_TIME_OUT && case_eye6){
                    //the eye stays right
                    case_eye6 = false;
                    case_eye7 = true;
                    timer_eye7 = millis();
                }
                else if (millis() - timer_eye7 >= LK_EYE_TIME_OUT && case_eye7){
                    eyesInlight(NEUTRAL_FROM_RIGHT);
                    case_eye7 = false;
                    case_eye1 = true;
                    timer_eye1 = millis();
                } 
            }
            break;
        case SADNESS:
            if(first_time_eye){
                eyesInlight(SADNESS_EYE);
                previous_emotion = SADNESS;
                first_time_eye = false;  
            }         
            break; 
        case EXCITEMENT:
            if(first_time_eye){
                previous_emotion = EXCITEMENT;
                first_time_eye = false;  
                timer_eye1 = millis() - EXC_EYE_TIME_OUT;
            }
            else {
                if(millis() - timer_eye1 >= EXC_EYE_TIME_OUT){
                    eyesInlight(EXCITEMENT_EYE);
                    timer_eye1 = millis();
                }
            }
            break;
        case JOY:
            if(first_time_eye){
                eyesInlight(JOY_EYE);
                previous_emotion = JOY;
                first_time_eye = false;  
            }         
            break;
        case GIGGLE:
            if(first_time_eye){
                eyesInlight(GIGGLE_EYE);
                previous_emotion = GIGGLE;
                first_time_eye = false;  
            }  
            break;
        case FEAR:
            if(first_time_eye){
                eyesInlight(FEAR_EYE);
                previous_emotion = FEAR;
                first_time_eye = false;  
            }         
            break;
        case ANGER:
            if(first_time_eye){
                previous_emotion = ANGER;
                eyesInlight(ANGER_EYE);
                first_time_eye = false;
            }
            break;        
        case DISGUST:
            if(first_time_eye){
                eyesInlight(DISGUST_EYE);
                previous_emotion = DISGUST;
                first_time_eye = false;  
            } 
            break;
        default: break;
    }
} 

void drawEye(bool eye[8][8], struct RGB color){
    for(uint16_t row=0; row < 8; row++){
        for(uint16_t column=0; column < 8; column++){
            if (eye[row][column] == 1)
                matrix.drawPixel(column, row, matrix.Color(color.r, color.g, color.b));
            else
                matrix.drawPixel(column, row, matrix.Color(0, 0, 0));
        }
    }
    matrix.show();
}
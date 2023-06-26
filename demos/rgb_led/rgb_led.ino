const int GREEN = 9 ;  
const int BLU = 12;  
const int RED = 8;  
  
const int delayTime = 20;  
  
void setup(){    
  pinMode(GREEN, OUTPUT);  
  pinMode(BLU, OUTPUT);  
  pinMode(RED, OUTPUT);  
  
  digitalWrite(GREEN, HIGH);  
  digitalWrite(BLU, HIGH);  
  digitalWrite(RED, HIGH);  
}  
  
int greenval;  
  
void loop(){  
  greenval = 255;  
  for( int i = 0 ; i < 255 ; i += 1 ){  
    greenval -= 1;  
    analogWrite( GREEN, 255 - greenval );  
    delay( delayTime );  
  }  
}  



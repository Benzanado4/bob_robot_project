#include <Wire.h>
#include <Adafruit_MLX90614.h>
#define ERR_TEMP 0.7

float calibrationSum = 0;               
unsigned int calibrationCounter = 0;    
float meanTemp;

unsigned long timer_calibration;

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setupThermoSensor(){
    mlx.begin();
    
    timer_calibration = millis();    
    while (millis() - timer_calibration < 1000){
        calibrateTemperature();        
    }
    meanTemp = calibrationSum / calibrationCounter;
    #if defined(DEVMODE)
        Serial.print("Thermosensor SETUP begin. Mean temperature:"); 
        Serial.println(meanTemp);
    #endif
}

void calibrateTemperature(){
    calibrationSum += mlx.readObjectTempC();
    calibrationCounter++;
}

boolean thermosensor(){
    float objectTemp = mlx.readObjectTempC();
    
    if(objectTemp >= meanTemp + ERR_TEMP){
        #if defined(DEVMODE)
            Serial.print("Thermo State: HAND DETECTED. Object temperature: ");
            Serial.println(objectTemp);
        #endif 
        return true;
    }
    return false;    
}

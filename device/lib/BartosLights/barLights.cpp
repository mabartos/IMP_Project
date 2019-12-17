
#include "barLights.h"

const uint8_t lightsPins[]={RED_LED,GREEN_LED,BLUE_LED};
const size_t countOfLights=sizeof(lightsPins)/sizeof(lightsPins[0]);

void setUpLights(){
    for(uint8_t i=0;i<countOfLights;i++){
    pinMode(lightsPins[i],OUTPUT);
    digitalWrite(lightsPins[i],LOW);
  }
}

void blickLED(uint8_t device,uint16_t delayTime){
  digitalWrite(device,LOW);
  delay(delayTime);
  digitalWrite(device,HIGH);
  delay(delayTime);
  digitalWrite(device,LOW);
}

// In procent
boolean changeIntensity(uint8_t device,uint8_t intensity){
  if(intensity >= 0 && intensity <= 100){
    float resultIntensity=(PWM_RANGE/100)*intensity;
    analogWrite(device,(uint16_t)resultIntensity);
    return true;
  }
  return false;
}

void increaseFading(uint8_t device){
  for(uint16_t i=0;i<PWM_RANGE;i++){
    analogWrite(device,i);
    delay(2);
  }
}

void decreaseFading(uint8_t device){
  for(uint16_t i=PWM_RANGE;i>0;i--){
    analogWrite(device,i);
    delay(2);
  }
}

// Intensity in Procent
void changeRGBColors(uint16_t redIntensity,uint16_t greenIntensity,uint16_t blueIntensity){
  changeIntensity(RED_LED,redIntensity);
  changeIntensity(GREEN_LED,greenIntensity);
  changeIntensity(BLUE_LED,blueIntensity);
}

void simpleSequence(){
  blickLED(RED_LED,500);
  blickLED(GREEN_LED,500);
  blickLED(BLUE_LED,500);

  increaseFading(RED_LED);
  delay(500);
  decreaseFading(RED_LED);
  delay(500);
}
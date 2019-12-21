/**
 *  Martin Bartos (xbarto96)
 *  Original (Last modified : 21.12.2019)
 */

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

void fadingIteration(uint8_t device, uint16_t countOfIterations){
  digitalWrite(device,LOW);
  for(uint16_t i=0;i<countOfIterations;i++){
    increaseFading(device);
    delay(100);
    decreaseFading(device);
    delay(100);
  }
}

void blickingIteration(uint8_t device, uint16_t countOfIterations){
  if(!digitalRead(device)){
    for(uint16_t i=0;i<countOfIterations;i++){
      blickLED(device,DEFAULT_DELAY);
    }
  }
}

// Intensity in Procent
void changeRGBColors(uint16_t redIntensity,uint16_t greenIntensity,uint16_t blueIntensity){
  changeIntensity(RED_LED,redIntensity);
  changeIntensity(GREEN_LED,greenIntensity);
  changeIntensity(BLUE_LED,blueIntensity);
}

void sequence1(){
  increaseFading(RED_LED);
  increaseFading(BLUE_LED);
  increaseFading(GREEN_LED);
  
  delay(400);

  decreaseFading(RED_LED);
  decreaseFading(BLUE_LED);
  decreaseFading(GREEN_LED);
}

void sequence2(){
  uint16_t seq2delay=500;
  blickLED(BLUE_LED,seq2delay);
  blickLED(RED_LED,seq2delay);
  blickLED(GREEN_LED,seq2delay);

  decreaseFading(BLUE_LED);
  decreaseFading(RED_LED);
  decreaseFading(GREEN_LED);

  increaseFadingToValue(BLUE_LED,20);
  increaseFadingToValue(RED_LED,20);
  increaseFadingToValue(GREEN_LED,20);

  delay(seq2delay);

  digitalWrite(BLUE_LED,LOW);
  digitalWrite(RED_LED,LOW);
  digitalWrite(GREEN_LED,LOW);
}

void sequence3(){
  uint16_t seq3delay=500;

  blickLED(RED_LED,seq3delay);
  blickLED(GREEN_LED,seq3delay);
  blickLED(BLUE_LED,seq3delay);

  increaseFadingToValue(GREEN_LED,60);
  increaseFadingToValue(BLUE_LED,60);
  delay(seq3delay);

  decreaseFading(GREEN_LED);
  decreaseFading(BLUE_LED);
}

void increaseFadingToValue(uint8_t device,uint8_t value){
  if(value>0 && value<=100){
    uint16_t resultValue=(value*PWM_RANGE)/100;
    for(uint16_t i=0;i<resultValue;i++){
      analogWrite(device,i);
      delay(2);
    }
  }
}

void decreaseFadingToValue(uint8_t device,uint8_t value){
  if(value>0 && value<=100){
    uint16_t resultValue=(value*PWM_RANGE)/100;
    for(uint16_t i=PWM_RANGE;i>=resultValue;i--){
      analogWrite(device,i);
      delay(2);
    }
  }
}
#ifndef BARTOS_LIGHTS
#define BARTOS_LIGHTS
#include <stdint.h>
#include <cstdlib>
#include <Arduino.h>

#define PWM_RANGE 1024
#define COUNT_OF_ITERATIONS 3
#define DEFAULT_DELAY 1000

#define GREEN_LED D1
#define RED_LED D2
#define BLUE_LED D3

extern const uint8_t lightsPins[];
extern const size_t countOfLights;

void setUpLights();
void blickLED(uint8_t device,uint16_t delayTime);

void fadingIteration(uint8_t device, uint16_t countOfIterations);
void blickingIteration(uint8_t device, uint16_t countOfIterations);

boolean changeIntensity(uint8_t device,uint8_t intensity);
void increaseFading(uint8_t device);
void decreaseFading(uint8_t device);
void changeRGBColors(uint16_t redIntensity,uint16_t greenIntensity,uint16_t blueIntensity);
void simpleSequence();

#endif //BARTOS_LIGHTS
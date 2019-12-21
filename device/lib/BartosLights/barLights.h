/**
 *  Martin Bartos (xbarto96)
 *  Original (Last modified : 21.12.2019)
 */

#ifndef BARTOS_LIGHTS
#define BARTOS_LIGHTS

#include <stdint.h>
#include <cstdlib>
#include <Arduino.h>

#define PWM_RANGE 1024
#define COUNT_OF_ITERATIONS 3
#define DEFAULT_DELAY 1000

// Ports
#define GREEN_LED D1
#define RED_LED D2
#define BLUE_LED D3

extern const uint8_t lightsPins[];
extern const size_t countOfLights;

// Main function to set up Lights
void setUpLights();

// Function for blick the lights
void blickLED(uint8_t device,uint16_t delayTime);

// Light fading for 'countOfIterations' times
void fadingIteration(uint8_t device, uint16_t countOfIterations);

// Light blicking for 'countOfIterations' times
void blickingIteration(uint8_t device, uint16_t countOfIterations);

// Change intensity of light
boolean changeIntensity(uint8_t device,uint8_t intensity);

// Increase light fading from 0% to specific value.
void increaseFadingToValue(uint8_t device,uint8_t value);

// Decrease light fading from 100% to specific value.
void decreaseFadingToValue(uint8_t device,uint8_t value);

// Increase light fading.
void increaseFading(uint8_t device);

// Decrease light fading.
void decreaseFading(uint8_t device);

// Change intensity of the RGB model
void changeRGBColors(uint16_t redIntensity,uint16_t greenIntensity,uint16_t blueIntensity);

void sequence1();
void sequence2();
void sequence3();


#endif //BARTOS_LIGHTS
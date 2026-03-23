#include "RGBLED.h"
#include<Arduino.h>

void RGBLED::RGBledBegin(int8_t pinR = 9, int8_t pinG = 10, int8_t pinB = 11){
    _pinB = pinB;
    _pinG = pinG;
    _pinR = pinR;

    pinMode(_pinR,OUTPUT);
    pinMode(_pinG,OUTPUT);
    pinMode(_pinB,OUTPUT);
}

void RGBLED::setColor(uint8_t R, uint8_t G, uint8_t B){
    analogWrite(_pinR,R);
    analogWrite(_pinG,G);
    analogWrite(_pinB,B);

}
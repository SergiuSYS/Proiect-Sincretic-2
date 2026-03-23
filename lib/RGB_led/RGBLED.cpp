#include "RGBLED.h"
#include<Arduino.h>

void RGBLED::begin(int8_t pinR = A0, int8_t pinG = A1, int8_t pinB = A2){
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
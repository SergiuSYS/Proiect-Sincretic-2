#ifndef RGBLED_H
#define RGBLED_H
#include <Arduino.h>

class RGBLED{
    public:
        void RGBledBegin(int8_t pinR = 9, int8_t pinG = 10, int8_t pinB = 11);
        void setColor(uint8_t R, uint8_t G, uint8_t B);
    private:
        int8_t _pinR;
        int8_t _pinG;
        int8_t _pinB;
};
#endif
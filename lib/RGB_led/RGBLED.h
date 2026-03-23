#ifndef RGBLED_H
#define RGBLED_H
#include <Arduino.h>

class RGBLED{
    public:
        void begin(int8_t pinR = A0, int8_t pinG = A1, int8_t pinB = A2);
        void setColor(uint8_t R, uint8_t G, uint8_t B);
    private:
        int8_t _pinR;
        int8_t _pinG;
        int8_t _pinB;
};
#endif
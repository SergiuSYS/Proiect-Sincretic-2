#ifndef WaterSensor_H
#define WaterSensor_H
#include <Arduino.h>

    class WaterSensor{
        public:
            void begin(int8_t pin = A6);
            bool isWhaterPresent(float threshold);
            float getWaterLevel();
        private:
            int8_t _pin;
    };
#endif
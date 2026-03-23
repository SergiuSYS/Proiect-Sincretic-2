#ifndef WaterSensor_H
#define WaterSensor_H
#include <Arduino.h>

    class WaterSensor{
        public:
            void waterSensorBegin(int8_t pin = A0);
            bool isWhaterPresent(float threshold);
            float getWaterLevel();
        private:
            int8_t _pin;
    };
#endif
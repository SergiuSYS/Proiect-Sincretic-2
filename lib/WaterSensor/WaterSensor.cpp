#include <Arduino.h>
#include "WaterSensor.h"

void WaterSensor::begin(int8_t pin = A6){
    _pin = pin;
    pinMode(_pin,INPUT);
}

float WaterSensor::getWaterLevel(){
    return analogRead(_pin);
}

bool WaterSensor::isWhaterPresent(float threshold){
  if(getWaterLevel() > threshold) return true;
  return false;
}
#include <Arduino.h>
#include <Wire.h>
#include "BMP280.h"
#include "WaterSensor.h"

BMP280 sensor1;
WaterSensor sensor2;


void setup() {
  Serial.begin(9600);
  sensor2.waterSensorBegin();
}

void loop() {
  Serial.println(sensor2.isWhaterPresent(300));
}

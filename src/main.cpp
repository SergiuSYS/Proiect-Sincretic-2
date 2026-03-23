#include <Arduino.h>
#include <Wire.h>
#include "BMP280.h"

BMP280 sensor;

void setup() {
    Wire.begin();
    sensor.begin();
    Serial.begin(9600);
}

void loop() {
  sensor.read();
  Serial.println(sensor.getData().press);
  delay(1000);
}

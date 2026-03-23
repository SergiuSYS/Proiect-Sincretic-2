#include <Arduino.h>
#include <Wire.h>
#include "BMP280.h"
#include "WaterSensor.h"
#include "RGBLED.h"

BMP280 sensor1;
WaterSensor sensor2;
RGBLED sensor3;

void setup() {
  Serial.begin(9600);
  sensor1.begin();
  sensor2.begin();
  sensor3.begin();
  sensor3.setColor(230, 100, 100);

}

void loop() {
  Serial.println(sensor2.isWhaterPresent(300));
}

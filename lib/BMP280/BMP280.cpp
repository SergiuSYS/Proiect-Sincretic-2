#include<Arduino.h>
#include<math.h>
#include "Wire.h"
#include "BMP280.h"

bool BMP280::begin(uint8_t address){
    _address = address;

    setConfig(1, 1, 3, 1);
    
    Wire.beginTransmission(_address);
    Wire.write(0x88);
    
    byte error = Wire.endTransmission(false);
    if (error != 0)
    {
        return false;
    }
    
    Wire.requestFrom(_address,(uint8_t)26);

    _calib.dig_T1 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_T2 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_T3 = (Wire.read()) | (Wire.read() << 8);

    _calib.dig_P1 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P2 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P3 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P4 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P5 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P6 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P7 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P8 = (Wire.read()) | (Wire.read() << 8);
    _calib.dig_P9 = (Wire.read()) | (Wire.read() << 8);

    return true;
}

void BMP280::setConfig(int8_t tempSemp, int8_t pressSemp, int8_t mode, int8_t filter){
    if(tempSemp > 7) tempSemp = 7;
    if(pressSemp > 7) pressSemp = 7;
    if(mode > 3) mode = 3;
    if(filter > 7) filter = 7;

    if(tempSemp < 1) tempSemp = 1;
    if(pressSemp < 1) pressSemp = 1;
    if(mode < 1) mode = 1;
    if(filter < 1) filter = 1;

    uint8_t ctrl_semp = ((tempSemp & 7) << 5) | ((pressSemp & 7) << 2) | (mode & 3);
    uint8_t ctrl_filter = (filter & 7) << 2;

    Wire.beginTransmission(_address);
    Wire.write(0xF4);
    Wire.write(ctrl_semp);
    Wire.write(ctrl_filter);
    Wire.endTransmission();
}

bool BMP280::read(){
    Wire.beginTransmission(_address);
    Wire.write(0xF7);
    
    byte error = Wire.endTransmission(false);
    if (error != 0)
    {
        return false;
    }
    
    Wire.requestFrom(_address,(uint8_t)6);

    for(int i = 0; i < 3; i++) _dataPress[i] = Wire.read();
    for(int i = 0; i < 3; i++) _dataTemp[i] = Wire.read();  

    return true;
}

BMP280::_data BMP280::getData(){
    int32_t adc_T = ((int32_t)_dataTemp[0] << 12) | ((int32_t)_dataTemp[1] << 4) | (((int32_t)_dataTemp[2] >> 4) & 0x0F);
    int32_t adc_P = ((int32_t)_dataPress[0] << 12) | ((int32_t)_dataPress[1] << 4) | ((int32_t)_dataPress[2] >> 4);

    return _data{
        compensateTemp(adc_T),
        compensatePress(adc_P)
    };
}

float BMP280::compensateTemp(int32_t adc_T){
    int32_t var1, var2, T;
    var1 = ((((adc_T >> 3) - ((int32_t)_calib.dig_T1 << 1))) * ((int32_t)_calib.dig_T2)) >> 11;
    var2 = (((((adc_T >> 4) - ((int32_t)_calib.dig_T1)) * ((adc_T >> 4) - ((int32_t)_calib.dig_T1))) >> 12) * ((int32_t)_calib.dig_T3)) >> 14;

    _tFine = var1 + var2;
    T = (_tFine * 5 + 128) >> 8;
    return (float)T /100.0;
}

float BMP280::compensatePress(int32_t adc_P){
    int64_t var1, var2, P;
    var1 = ((int64_t)_tFine) - 128000;
    var2 = var1 * var1 * (int64_t)_calib.dig_P6;
    var2 = var2 + ((var1 * (int64_t)_calib.dig_P5) << 17);
    var2 = var2 + (((int64_t)_calib.dig_P4) << 35);
    var1 = ((var1 * var1 * (int64_t)_calib.dig_P3) >> 8) + ((var1 * (int64_t)_calib.dig_P2) << 12);
    var1 = (((((int64_t)1) << 47) + var1) * ((int64_t)_calib.dig_P1)) >> 33;

    if ( var1 == 0) return 0.00;
    
    P = 1048576 - adc_P;
    P = (((P << 31) - var2) * 3125)/var1;
    var1 = (((int64_t)_calib.dig_P9) * (P >> 13) * (P >> 13)) >> 25;
    var2 = (((int64_t)_calib.dig_P8) * P) >> 19;
    P = ((P + var1 + var2) >> 8) + (((int64_t)_calib.dig_P7) << 4);

    return (float)P/256/100;
    
}
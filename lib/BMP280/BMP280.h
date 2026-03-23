#ifndef BMP280_H
#define BMP280_H
#include <Arduino.h>

class BMP280{
    public:
        struct _data
        {
            float temp;
            float press;
        };
        
        bool begin(uint8_t address = 0x76);
        void setConfig(int8_t tempSemp, int8_t pressSemp, int8_t mode, int8_t filter);
        bool read();
        // BMP280::_data forceRead(); de adaugat mai tarziu 
        BMP280::_data getData();
        float getAltitude(int16_t seaLevelHp);

    private:
        byte _dataTemp[3];
        byte _dataPress[3];
        

        float compensateTemp(int32_t adc_T);
        float compensatePress(int32_t adc_P);

        struct CalibrationData
        {
            uint16_t dig_T1;
            int16_t dig_T2;
            int16_t dig_T3;

            uint16_t dig_P1;
            int16_t dig_P2;
            int16_t dig_P3;
            int16_t dig_P4;
            int16_t dig_P5;
            int16_t dig_P6;
            int16_t dig_P7;
            int16_t dig_P8;
            int16_t dig_P9;
        };
        
        int32_t _tFine;
        uint8_t _address;
        CalibrationData _calib;


};



#endif
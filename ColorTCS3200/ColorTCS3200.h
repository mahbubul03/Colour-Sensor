#ifndef ColorTCS3200_h
#define ColorTCS3200_h

#include <Arduino.h>

class ColorTCS3200 {
public:
    ColorTCS3200(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out);

    void begin();                   // call in setup()
    void setFrequencyScaling20();   // 20% (most common choice)
    void setFrequencyScaling100();  // 100%
    void setFrequencyScaling2();    // 2%
    void setFrequencyScalingOff();  // off

    uint16_t readRawRed();          // returns averaged pulse length
    uint16_t readRawGreen();
    uint16_t readRawBlue();

    // Most useful version — reads all three colors at once
    void readRGB(uint16_t &r, uint16_t &g, uint16_t &b);

    // Simple dominant color detection
    const char* getColorName();

private:
    uint8_t _pinS0, _pinS1, _pinS2, _pinS3, _pinOUT;

    uint16_t _readFiltered(uint8_t s2_state, uint8_t s3_state, uint8_t samples = 10);
    void _setMux(uint8_t s2, uint8_t s3);
};

#endif
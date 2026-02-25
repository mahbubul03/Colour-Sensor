#include "ColorTCS3200.h"

ColorTCS3200::ColorTCS3200(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t out) {
    _pinS0  = s0;
    _pinS1  = s1;
    _pinS2  = s2;
    _pinS3  = s3;
    _pinOUT = out;
}

void ColorTCS3200::begin() {
    pinMode(_pinS0,  OUTPUT);
    pinMode(_pinS1,  OUTPUT);
    pinMode(_pinS2,  OUTPUT);
    pinMode(_pinS3,  OUTPUT);
    pinMode(_pinOUT, INPUT);

    // Default = 20% scaling (most usable range for Arduino)
    setFrequencyScaling20();
}

void ColorTCS3200::setFrequencyScaling20() {
    digitalWrite(_pinS0, HIGH);
    digitalWrite(_pinS1, LOW);
}

void ColorTCS3200::setFrequencyScaling100() {
    digitalWrite(_pinS0, HIGH);
    digitalWrite(_pinS1, HIGH);
}

void ColorTCS3200::setFrequencyScaling2() {
    digitalWrite(_pinS0, LOW);
    digitalWrite(_pinS1, HIGH);
}

void ColorTCS3200::setFrequencyScalingOff() {
    digitalWrite(_pinS0, LOW);
    digitalWrite(_pinS1, LOW);
}

void ColorTCS3200::_setMux(uint8_t s2, uint8_t s3) {
    digitalWrite(_pinS2, s2);
    digitalWrite(_pinS3, s3);
    delay(12);   // give filter some settling time
}

uint16_t ColorTCS3200::_readFiltered(uint8_t s2_state, uint8_t s3_state, uint8_t samples) {
    _setMux(s2_state, s3_state);

    unsigned long sum = 0;
    for(uint8_t i = 0; i < samples; i++) {
        sum += pulseIn(_pinOUT, LOW, 30000UL);  // timeout ~30 ms
    }
    return (uint16_t)(sum / samples);
}

uint16_t ColorTCS3200::readRawRed() {
    return _readFiltered(LOW, LOW);
}

uint16_t ColorTCS3200::readRawGreen() {
    return _readFiltered(HIGH, HIGH);
}

uint16_t ColorTCS3200::readRawBlue() {
    return _readFiltered(LOW, HIGH);
}

void ColorTCS3200::readRGB(uint16_t &r, uint16_t &g, uint16_t &b) {
    r = readRawRed();
    g = readRawGreen();
    b = readRawBlue();
}

const char* ColorTCS3200::getColorName() {
    uint16_t r, g, b;
    readRGB(r, g, b);

    if (r < g && r < b) return "RED";
    if (g < r && g < b) return "GREEN";
    if (b < r && b < g) return "BLUE";
    
    return "UNKNOWN";
}
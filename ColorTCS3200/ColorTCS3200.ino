#include "ColorTCS3200.h"

// Pin numbers — change according to your wiring
#define S0 5
#define S1 6
#define S2 7
#define S3 8
#define SENSOR_OUT 4

ColorTCS3200 color(S0, S1, S2, S3, SENSOR_OUT);

void setup() {
  Serial.begin(115200);
  delay(200);
  
  color.begin();
  Serial.println("TCS3200 Color Sensor Library Ready");
}

void loop() {
  uint16_t r, g, b;
  color.readRGB(r, g, b);

  Serial.print("R: "); Serial.print(r);
  Serial.print("  G: "); Serial.print(g);
  Serial.print("  B: "); Serial.print(b);
  Serial.print("   →  ");

  Serial.print("Detected: ");
  Serial.println(color.getColorName());

  Serial.println("---------------------");
  
  delay(1200);
}

#include "ADXL335.h"
const float alpha = 0.5;
double pitch, roll;
double fXg = 0;
double fYg = 0;
double fZg = 0;

// CONSTRUCTOR
ADXL335 acelerometro(A0, A1, A2);

void setup(void) {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  acelerometro.preset();
}

void loop() {
  float xG = acelerometro.getGX();
  float yG = acelerometro.getGY();
  float zG = acelerometro.getGZ();

  //Low Pass Filter
  fXg = xG * alpha + (fXg * (1.0 - alpha));
  fYg = yG * alpha + (fYg * (1.0 - alpha));
  fZg = zG * alpha + (fZg * (1.0 - alpha));

  Serial.print(xG);
  Serial.print(":");
  Serial.print(yG);
  Serial.print(":");
  Serial.print(zG);
  Serial.println(":");

 
  //Roll & Pitch Equations
  roll  = (atan2(-fYg, fZg) * 180.0) / PI;
  pitch = (atan2(fXg, sqrt(fYg * fYg + fZg * fZg)) * 180.0) / PI;

  Serial.print(pitch);
  Serial.print(":");
  Serial.print(roll);
  
}


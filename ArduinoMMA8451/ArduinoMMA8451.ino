/**************************************************************************/
/*!
    @file     Adafruit_MMA8451.h
    @author   K. Townsend (Adafruit Industries)
    @license  BSD (see license.txt)

    This is an example for the Adafruit MMA8451 Accel breakout board
    ----> https://www.adafruit.com/products/2019

    Adafruit invests time and resources providing this open source code,
    please support Adafruit and open-source hardware by purchasing
    products from Adafruit!

    @section  HISTORY

    v1.0  - First release
*/
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MMA8451.h>
#include <Adafruit_Sensor.h>

Adafruit_MMA8451 mma = Adafruit_MMA8451();

const float alpha = 0.5;
double pitch, roll;
double fXg = 0;
double fYg = 0;
double fZg = 0;

void setup(void) {
  Serial.begin(9600);

  Serial.println("Adafruit MMA8451 test!");


  if (! mma.begin()) {
    //Serial.println("Couldnt start");
    while (1);
  }
  Serial.println("MMA8451 found!");

  mma.setRange(MMA8451_RANGE_2_G);

  //  Serial.print("Range = "); Serial.print(2 << mma.getRange());
  //  Serial.println("G");

}

void loop() {
  mma.read();


  double Xg, Yg, Zg;
  Xg = mma.x;
  Yg = mma.y;
  Zg = mma.z;
  //Low Pass Filter
  fXg = Xg * alpha + (fXg * (1.0 - alpha));
  fYg = Yg * alpha + (fYg * (1.0 - alpha));
  fZg = Zg * alpha + (fZg * (1.0 - alpha));

  //Roll & Pitch Equations
  roll  = (atan2(-fYg, fZg) * 180.0) / PI;
  pitch = (atan2(fXg, sqrt(fYg * fYg + fZg * fZg)) * 180.0) / PI;

  Serial.print(pitch);
  Serial.print(":");
  Serial.print(roll);
  Serial.print(":");
  
  // print orientation
  uint8_t o = mma.getOrientation();
  Serial.print(o);
  Serial.print(":");

  // print accel in each dimension
  sensors_event_t event;
  mma.getEvent(&event);
  /* Display the results (acceleration is measured in m/s^2) */
  Serial.print(event.acceleration.x);
  Serial.print(":");
  Serial.print(event.acceleration.y);
  Serial.print(":");
  Serial.print(event.acceleration.z);
  Serial.println();
}

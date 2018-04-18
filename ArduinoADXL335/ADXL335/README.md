# Arduino Library for ADXL335

## ADXL335( int x, int y, int z )

Constructor. x, y and z parameters are analog pins connected to ADXL analog output.

## preset()

Calibrate ADXL335 with default values.

## calibrate()

Manual calibration. Must be done with all 6 valid positions (y, -y, x, -x, z, -z).

## getRawX(), getRawY(), getRawZ()

Read axis acceleration from ADXL335 as raw analogRead() data (with average).

## getGX(), getGY(), getGZ()

Read axis acceleration from ADXL335 as G units (9.8m/s² = 1G)

# Example

```Arduino

#include "ADXL335.h"

// CONSTRUCTOR
ADXL335 acelerometro(A0, A1, A2);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  analogReference(EXTERNAL);
  acelerometro.preset();

}

void loop() {

  float xG = acelerometro.getGX();
  float yG = acelerometro.getGY();
  float zG = acelerometro.getGZ();

  Serial.print(xG);
  Serial.print("G, ");
  Serial.print(yG);
  Serial.print("G, ");
  Serial.print(zG);
  Serial.println("G");
  Serial.print("Inclinacao em graus: ");
  Serial.println(anguloG);
  Serial.println();

  delay(500);
}

```

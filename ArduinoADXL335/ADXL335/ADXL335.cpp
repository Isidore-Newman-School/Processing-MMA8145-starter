/*
Copyright 2017 Code Decay
Authors: Renan Yuri Lino, Douglas Navarro

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "ADXL335.h"

ADXL335::ADXL335(int x, int y, int z) {
  pinX = x; pinY = y; pinZ = z;
  xMin = 512; xMax = 512; yMin = 512; yMax = 512; zMin = 512; zMax = 512;
  samples = 10;
}

ADXL335::~ADXL335(){

}

int ADXL335::averageRead(int pin) {
  long value = 0;
  for (int i = 0; i < samples; i++)
  {
    value += analogRead(pin);
  }
  return value/samples;
}

int ADXL335::getRawX() {
  return averageRead(pinX);
}

int ADXL335::getRawY() {
  return averageRead(pinY);
}

int ADXL335::getRawZ() {
  return averageRead(pinZ);
}

double ADXL335::getGX() {
  int x = getRawX();
  return map(x, xMin, xMax, -1000, 1000)/1000.0;
}

double ADXL335::getGY() {
  int y = getRawY();
  return map(y, xMin, xMax, -1000, 1000)/1000.0;
}

double ADXL335::getGZ() {
  int z = getRawX();
  return map(z, xMin, xMax, -1000, 1000)/1000.0;
}

void ADXL335::calibrate() {
  int x = getRawX();
  int y = getRawY();
  int z = getRawZ();
  if (x < xMin) xMin = x;
  if (x > xMax) xMax = x;

  if (y < yMin) yMin = y;
  if (y > yMax) yMax = y;

  if (z < zMin) zMin = z;
  if (z > zMax) zMax = z;
}

void ADXL335::preset() {
  xMin = 394;
  xMax = 593;

  yMin = 393;
  yMax = 591;

  zMin = 401;
  zMax = 601;
}

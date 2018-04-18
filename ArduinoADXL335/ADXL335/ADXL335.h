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

#ifndef ADXL335_H
#define ADXL335_H

#include "Arduino.h"

class ADXL335 {
public:
  ADXL335(int x, int y, int z);
  ~ADXL335();
  int getRawX();
  int getRawY();
  int getRawZ();
  double getGX();
  double getGY();
  double getGZ();
  void calibrate();
  void preset();
private:
  int averageRead(int pin);
  int xMin, xMax, yMin, yMax, zMin, zMax, pinX, pinY, pinZ, samples;
};

#endif

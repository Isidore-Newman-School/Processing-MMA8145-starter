/********************************************************************************
 * ADXL345 Library Examples- pitch_roll.pde                                      *
 *                                                                               *
 * Copyright (C) 2012 Anil Motilal Mahtani Mirchandani(anil.mmm@gmail.com)       *
 *                                                                               *
 * License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html> *
 * This is free software: you are free to change and redistribute it.            *
 * There is NO WARRANTY, to the extent permitted by law.                         *
 *                                                                               *
 *********************************************************************************/

// If you are working with Arduino Mega
// sudo ln -s /dev/ttyACM0 /dev/ttyS8

import processing.serial.*;

PShape rover;
Serial fd;

int pitch = 0;
int roll = 0;
int orientation = 0;

float accelX, accelY, accelZ;

void setup () 
{
  size(640, 360, P3D); 
  //Connect to the corresponding serial port
  printArray(Serial.list());
  fd = new Serial(this, Serial.list()[1], 9600);
  // Defer callback until new line
  fd.bufferUntil('\n');
  rover = loadShape("tinker.obj");
}

void draw () 
{
  background(0.5);
  arc(100, 100, 100, 100, 0, radians(pitch+90));
  displayRover();
  //drawCube();
  printData();
  delay(50);
}

void printData() {
  print("Pitch: ");
  print(pitch);
  print(", Roll: ");
  println(roll);
  println("AccelX: ");
  print(accelX);
  print(", AccelY: ");
  print(accelY);
  print(", AccelZ: ");
  println(accelZ);
  println("Orientation: " + orientation);
}

void displayRover() {
  lights();
  pushMatrix();
  
  translate(width/2, height/2);
  scale(6);
  rotateX(radians(90));
  rotateY(radians(pitch));
  rotateZ(radians(180));
  shape(rover, 0, 0);
  popMatrix();
}

void serialEvent (Serial fd) 
{
  try {
    // get the ASCII string:
    String rpstr = fd.readStringUntil('\n');
    if (rpstr != null) {
      String[] list = split(rpstr, ':');
      pitch = ((int)float(list[0]));
      roll = ((int)float(list[1]));
      orientation = ((int)float(list[2]));
      accelX = float(list[3]);
      accelY = float(list[4]);
      accelZ = float(list[5]);
    }
  }
  catch(Exception e) {
    //println(e);
  }
}
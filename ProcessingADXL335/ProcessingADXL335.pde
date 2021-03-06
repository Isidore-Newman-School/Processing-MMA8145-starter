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

int orientation = 0;

float accelX, accelY, accelZ, pitch, roll, yaw;

PImage plane;

void setup () 
{
  size(640, 360, P3D); 
  //Connect to the corresponding serial port
  printArray(Serial.list());
  fd = new Serial(this, Serial.list()[1], 9600);
  // Defer callback until new line
  fd.bufferUntil('\n');
  rover = loadShape("tinker.obj");
  plane = loadImage("plane.png");
}

void draw () 
{
  background(0.5);
  arc(100, 100, 100, 100, 0, radians(pitch+90));
  displayRover();
  displayPlane();
  //drawCube();
  printData();
  delay(50);
}

void displayPlane() {
  pushMatrix();
  translate(100, 100);
  rotate(radians(roll));
  image(plane, 0, 0);
  popMatrix();
}

void printData() {
  print("Pitch: ");
  print(pitch);
  print(", Roll: ");
  println(roll);
  print("AccelX: ");
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
  rotateX(radians(roll+90));
  rotateY(radians(pitch));
  shape(rover, 20, 0);
  popMatrix();
}

void serialEvent (Serial fd) 
{
  try {
    // get the ASCII string:
    String rpstr = fd.readStringUntil('\n');
    if (rpstr != null) {
      String[] list = split(rpstr, ':');
      
      accelX = float(list[0]);
      accelY = float(list[1]);
      accelZ = float(list[2]);
      pitch = float(list[3]);
      roll = float(list[4]);
      yaw = float(list[5]);
    }
  }
  catch(Exception e) {
    //println(e);
  }
}
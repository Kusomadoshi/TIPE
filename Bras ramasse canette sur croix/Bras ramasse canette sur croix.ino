/*
  take the can.ino

 This example commands to the Braccio to take a can from the table on the x 

 Created on 01/05/2022
 by Silver

 This example is in the public domain.
*/

#include <Braccio.h>
#include <Servo.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


void setup() {  

  Braccio.begin();
}

void loop() {

 

  //The braccio will go to the right position to grab the can
  Braccio.ServoMovement(20,          85,  90, 0, 120,  90,   0);

  //Only M2 moves, for the gripper to be at the level of the can
  Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );

  delay(500);
  //Only M6 moves, Gripper closed to grab the can
  Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  73 );
  delay(500);
  //Only M2 moves, to check if the braccia indeed grabbed the can
  Braccio.ServoMovement(20,         85,   90, 0,  120,  90, 73 );
  delay(1000);
  //Putting back the Can back on the x
  Braccio.ServoMovement(30,           85,  60, 0, 120,  90,  73 );
  Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );

}



#include <Braccio.h>
#include <Servo.h>

#include "Seeed_LDC1612.h"

LDC1612 sensor;

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;


void setup() {  

  Braccio.begin();
  Serial.begin(115200);
  sensor.init();

  if(sensor.single_channel_config(CHANNEL_0))
  {
      Serial.println("can't detect sensor!");
      while(1);
   }
  //The braccio will go to the right position to grab the can
  Braccio.ServoMovement(20,          85,  90, 0, 120,  90,   0);

  //Only M2 moves, for the gripper to be at the level of the can
  Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );
}

void loop() {

  

  
  u32 result_channel1=0;
  u32 result_channel2=0;

  /*shows the status of sensor.*/
  //sensor.get_sensor_status();

  /*Get channel 0 result and parse it.*/
  sensor.get_channel_result(CHANNEL_0,&result_channel1);


  if (result_channel1>44300000){
          
  
  //Only M6 moves, Gripper closed to grab the can
  Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  73 );
  delay(500);
  //Only M2 moves, to check if the braccia indeed grabbed the can
  Braccio.ServoMovement(20,         85,   110, 0,  120,  90, 73 );
  Braccio.ServoMovement(20,         0,   110, 0,  120,  90, 73 );
  delay(1000);
  //Putting back the Can back on the x
  Braccio.ServoMovement(30,           0,  60, 0, 120,  90,  73 );
  Braccio.ServoMovement(20,           0,  60, 0, 120,  90,  0 );
  Braccio.ServoMovement(20,           85,  90, 0, 120,  90,  0 );
  Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );
    
  }

}



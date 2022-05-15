/*
  take the can.ino

 This example commands to the Braccio to take a can from the table on the x 

 Created on 01/05/2022
 by Silver

 This example is in the public domain.
*/

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
const byte TRIGGER_PIN = 2; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
const float SOUND_SPEED = 340.0 / 1000;
const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
var state = 0

void setup() {  
   /* Initialise le port série */
  Serial.begin(115200);
   
  /* Initialise les broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  digitalWrite(TRIGGER_PIN, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(ECHO_PIN, INPUT);


  Braccio.begin();
  Serial.begin(115200);
  delay(100);
  Serial.println("start!");

  sensor.init();

  if(sensor.single_channel_config(CHANNEL_0))
  {
      Serial.println("can't detect sensor!");
      while(1);
   }
}

void loop() {
  if (state ==0){
    Braccio.ServoMovement(20,          85,  90, 0, 120,  90,   0);
      /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
    digitalWrite(TRIGGER_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN, LOW);
  
  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
    long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
   
  /* 3. Calcul la distance à partir du temps mesuré */
    float distance_mm = measure / 2.0 * SOUND_SPEED;
    if (distance_mm>100) and (distance_mm<250){
      state = 1
    }
  }
  
  if (state == 1){
    //The braccio will go to the right position to grab the can
    Braccio.ServoMovement(20,          85,  90, 0, 120,  90,   0);

  //Only M2 moves, for the gripper to be at the level of the can
    Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );
    Braccio.ServoMovement(20,          85,  90, 0, 120,  90,   0);

  //Only M2 moves, for the gripper to be at the level of the can
    Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );
    //Only M6 moves, Gripper closed to grab the can
    Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  73 );
    delay(500);
  //Only M2 moves, to check if the braccia indeed grabbed the can
    Braccio.ServoMovement(20,         85,   90, 0,  120,  90, 73 );
    delay(1000);
  //Putting back the Can back on the x
    Braccio.ServoMovement(30,           85,  60, 0, 120,  90,  73 );
    Braccio.ServoMovement(20,           85,  60, 0, 120,  90,  0 );
    if (distance_mm<100) or (distance_mm>250){
      state = 0
}
}
}
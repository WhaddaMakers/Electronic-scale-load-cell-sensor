/**

  @@@@@@@@@@@@@@@@@@@@@@                                                                                                                               
  @@@@@@@@@@@@@@@@@@@@@@             @@@.    @@@    @@@.     @@@@    @@@@        @@@@@@@@@        @@@@@@@@@@@@@.     .@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@%%@@@%%@@@%%@@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@@@@@@@        @@@@@@@@@@@@@@     @@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@  @@@  @@@  @@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@            @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@   @    @   @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@@@@@@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@@@@@@@@ 
  @@@@@            @@@@@             @@@@###@@@@@##@@@@@     @@@@    @@@@      @@@@@@@@@@@@       #@@@@@###@@@@@     ##@@@@@###@@@@       @@@@@@@@@@@
  @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@     @@@@    @@@@      @@@@    @@@@@      @@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@     @@@@
  @@@@@@@@@@@@@@@@@@@@@@

  Whadda Electronic scale load cell example code

  This example code initializes the electronic scale module with the zero and calibration factors set by the user.
  Once the module is initialized, the program reads the current weight on the sensor and prints the results (both single and averaged readings)
  in the serial monitor.

  For the best results, it is recommended to first run the calibrate_sensor sketch and paste the resulting calibration factors below to have accurate results.

  For more information about the Whadda Electronic scale load sensor, consult the manual at the WPSE471 product page on whadda.com

  This example is based on the demo program for the HX711 library for Arduino
  https://github.com/bogde/HX711
  MIT License
  (c) 2018 Bogdan Necula
**/
#include "HX711.h"

// PASTE DEFINE STATEMENTS FROM CALIBRATION SKETCH HERE
// VVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVVV
#define ZERO_FACTOR 69251.f
#define CALIBRATION_FACTOR -105500.00f
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 2;
const int LOADCELL_SCK_PIN = 3;


HX711 scale;

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale...");

  // Initialize library with data output pin, clock input pin and gain factor.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);


  scale.set_scale(CALIBRATION_FACTOR);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.set_offset(ZERO_FACTOR);

  Serial.println("Initializing done!");

  Serial.println("Readings:");
}

void loop() {
  Serial.print("one reading:\t");
  Serial.print(scale.get_units(), 3);
  Serial.print("\t| average:\t");
  Serial.println(scale.get_units(10), 3);
  
  delay(10);

}

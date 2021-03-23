/*
  @@@@@@@@@@@@@@@@@@@@@@                                                                                                                               
  @@@@@@@@@@@@@@@@@@@@@@             @@@.    @@@    @@@.     @@@@    @@@@        @@@@@@@@@        @@@@@@@@@@@@@.     .@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@%%@@@%%@@@%%@@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@@@@@@@        @@@@@@@@@@@@@@     @@@@@@@@@@@@@@        @@@@@@@@@  
  @@@@@  @@@  @@@  @@@@@             @@@@    @@@    @@@@     @@@@    @@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@            @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@   @@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@   @@@@ 
  @@@@@   @    @   @@@@@             @@@@   @@@@    @@@@     @@@@@@@@@@@@       @@@@@@@@@@@        @@@@@   @@@@@       @@@@@   @@@@       @@@@@@@@@@@ 
  @@@@@            @@@@@             @@@@###@@@@@##@@@@@     @@@@    @@@@      @@@@@@@@@@@@       #@@@@@###@@@@@     ##@@@@@###@@@@       @@@@@@@@@@@
  @@@@@@@@@@@@@@@@@@@@@@             @@@@@@@@@@@@@@@@@@@     @@@@    @@@@      @@@@    @@@@@      @@@@@@@@@@@@@@     @@@@@@@@@@@@@@      @@@@     @@@@
  @@@@@@@@@@@@@@@@@@@@@@

  Whadda Electronic scale load cell calibration code

  This calibration code takes the user through the necessary steps
  to find the calibration factors required to get accurate weight readings from the sensor.

  For more information about the Whadda Electronic scale load sensor, consult the manual at the WPSE471 product page on whadda.com

  Based on Example using the SparkFun HX711 breakout board with a scale
 
  By: Nathan Seidle
  SparkFun Electronics
  Date: November 19th, 2014
  License: This code is public domain but you buy me a beer if you use this and we meet someday (Beerware license).
 
  This is the calibration sketch. Use it to determine the calibration_factor that the main example uses. It also
  outputs the zero_factor useful for projects that have a permanent mass on the scale in between power cycles.
 
  Setup your scale and start the sketch WITHOUT a weight on the scale
  Once readings are displayed place the weight on the scale
  Press +/- or a/z to adjust the calibration_factor until the output readings match the known weight
  Press d when done, copy the resulting #define statements into the read_weight.ino sketch
 
 This example assumes kilograms (kgs)
 
 Your calibration factor may be very positive or very negative. It all depends on the setup of your scale system
 and the direction the sensors deflect from zero state
 This example code uses bogde's excellent library: https://github.com/bogde/HX711
 bogde's library is released under a GNU GENERAL PUBLIC LICENSE
 Arduino pin 3 -> HX711 CLK
 Arduino pin 2 -> HX711 DATA
 5V -> VCC
 GND -> GND
 
 Most any pin on the Arduino Uno will be compatible with DOUT/CLK.
 
 The HX711 board can be powered from 2.7V to 5V so the Arduino 5V power should be fine.
 
*/

#include "HX711.h" //This library can be obtained here http://librarymanager/All#Avia_HX711

#define LOADCELL_DOUT_PIN  2
#define LOADCELL_SCK_PIN  3

HX711 scale;

float calibration_factor = -105500; //-105500 worked for standard Whadda load cell (produces result in kgs)
long zero_factor = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("HX711 calibration sketch");
  Serial.println("Remove all weight from scale");
  Serial.println("After readings begin, place known weight on scale");
  Serial.println("Press + or a to increase calibration factor");
  Serial.println("Press - or z to decrease calibration factor");
  Serial.println("Press d or D when done");

  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale();
  scale.tare();  //Reset the scale to 0

  zero_factor = scale.read_average(); //Get a baseline reading
  Serial.print("Zero factor: "); //This can be used to remove the need to tare the scale. Useful in permanent scale projects.
  Serial.println(zero_factor);
}

void loop() {

  scale.set_scale(calibration_factor); //Adjust to this calibration factor

  Serial.print("Reading: ");
  Serial.print(scale.get_units(), 3);
  Serial.print(" kgs"); //Change this to kg and re-adjust the calibration factor if you follow SI units like a sane person
  Serial.print(" calibration_factor: ");
  Serial.print(calibration_factor);
  Serial.println();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 1000;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 1000;
    else if (temp == 'd' || temp == 'D') {
      Serial.println();
      Serial.println("Calibration procedure finished");
      Serial.println("Copy following define statements to read_weight sketch:");
      Serial.print("#define ZERO_FACTOR ");
      Serial.print(zero_factor);
      Serial.println(".f");
      Serial.print("#define CALIBRATION_FACTOR ");
      Serial.print(calibration_factor);
      Serial.println("f");
      while(1);
    }
  }

}

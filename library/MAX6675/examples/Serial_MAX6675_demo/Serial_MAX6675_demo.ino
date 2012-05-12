/*
 Demonstration sketch for Hobbybotics MAX6675 Thermocouple breakout board.
 
 Reads temperature from MAX6675 in celsius and fahrenheit.  Prints results to serial monitor.
*/

#include <MAX6675.h>

MAX6675 thermocouple;
  
void setup() {
  Serial.begin(9600);
  thermocouple.init(4, 5, 6);
  
  Serial.println("MAX6675 test");
  // wait for MAX chip to stabilize
  delay(500);
}

void loop() {
  // basic readout test, just print the current temp
  
   Serial.print("C = "); 
   Serial.println(float(thermocouple.measure(TEMPC)));
   Serial.print("F = ");
   Serial.println(float(thermocouple.measure(TEMPF)));
 
   delay(1000);
}
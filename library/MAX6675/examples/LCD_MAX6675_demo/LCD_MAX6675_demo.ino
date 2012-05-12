/*
 Demonstration sketch for Hobbybotics MAX6675 Thermocouple breakout board.
 
 Reads temperature from MAX6675 in celsius and fahrenheit.  Prints results to I2C LCD.
*/

#include <MAX6675.h>
#include <LCD.h>
#include <Wire.h>

MAX6675 thermocouple;

// Default I2C address for LCD is 0
LCD lcd;

// make a degree symbol
uint8_t degree[8]  = {140,146,146,140,128,128,128,128};

void setup() {
  lcd.begin(20, 4);
  lcd.createChar(0, degree);
  
  thermocouple.init(4, 5, 6);

  // wait for MAX6675 to stabilize
  delay(500);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("MAX6675 test");
}

void loop() {
  float temp_c;
  float temp_f;
  
  // Read values from the sensor
  temp_c = thermocouple.measure(TEMPC);
  temp_f = thermocouple.measure(TEMPF);
  
  lcd.setCursor(0,1);
  lcd.print(temp_c);
  lcd.write((byte)0);
  lcd.print("C ");
  lcd.print(temp_f);
  lcd.write((byte)0);
  lcd.print('F');
  
  delay(1000);
}
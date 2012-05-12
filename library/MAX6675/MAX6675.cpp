/*-----------------------------------------------------------------------------------------------
 * File: MAX6675.cpp
 * Function: MAX6675 Thermocouple library
 * Description: MAX6675 Type-K Thermocouple Library for the Hobbybotics MAX6675 breakout board.
 * Created by Curtis Brooks, May 6, 2012.
 * Updated: N/A
 * Released into the public domain.
 * 
 * Notes: Modified MAX6675 library by Adafruit <https://github.com/adafruit/MAX6675-library>
 * ----------------------------------------------------------------------------------------------*/

// Add necessary include files
#include "MAX6675.h"
 
#include <avr/pgmspace.h>
#include <util/delay.h>
#include <stdlib.h>
 
/*-----------------------------------------------------------------------------------------------
 * Public Methods
 * ----------------------------------------------------------------------------------------------*/

void MAX6675::init() {
  _DO = 4;
  _CLK = 5;
  _CS = 6;
  
  //define pin modes
  pinMode(_CS, OUTPUT);
  pinMode(_CLK, OUTPUT); 
  pinMode(_DO, INPUT);

  digitalWrite(_CS, HIGH);
}
 
void MAX6675::init(uint8_t DO, uint8_t CLK, uint8_t CS) {
  _DO = DO;
  _CLK = CLK;
  _CS = CS;
  
  //define pin modes
  pinMode(_CS, OUTPUT);
  pinMode(_CLK, OUTPUT); 
  pinMode(_DO, INPUT);

  digitalWrite(_CS, HIGH);
}

double MAX6675::measure(uint8_t type) {
  double value;
  
  switch(type) {
    case TEMPC : value = tempC(); break;
    case TEMPF : value = tempF(); break;
  }
  return value;
}

/*-----------------------------------------------------------------------------------------------
 * Private Methods
 * ----------------------------------------------------------------------------------------------*/
double MAX6675::tempC() {
  uint16_t v;

  digitalWrite(_CS, LOW);
  _delay_ms(1);

  v = spiRead();
  v <<= 8;
  v |= spiRead();

  digitalWrite(_CS, HIGH);

  if (v & 0x4) {
    // uh oh, no thermocouple attached!
    return NAN; 
    //return -100;
  }

  v >>= 3;

  return v*0.25;
}

double MAX6675::tempF() {
  return tempC() * 9.0/5.0 + 32;
}

byte MAX6675::spiRead() { 
  int i;
  byte d = 0;

  for (i=7; i>=0; i--)
  {
    digitalWrite(_CLK, LOW);
    _delay_ms(1);
    if (digitalRead(_DO)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    digitalWrite(_CLK, HIGH);
    _delay_ms(1);
  }

  return d;
}



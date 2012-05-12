#ifndef MAX6675_h
#define MAX6675_h

// Keep compatability with Arduino 1.0 and below
#if ARDUINO>=100
#include <Arduino.h>             // Arduino 1.0
#else
#include <WProgram.h>            // Arduino 0023 and below
#endif

enum {
  TEMPC,
  TEMPF
};

class MAX6675 {
  public:
    void init();
    void init(uint8_t DO, uint8_t CLK, uint8_t CS);
    double measure(uint8_t type);
        
  private:
    double tempC();
    double tempF();
    uint8_t spiRead();
    
    int8_t _DO, _CS, _CLK;
};

#endif
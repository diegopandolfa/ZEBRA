
#ifndef Morse_h
#define Morse_h
#include "Arduino.h"

class Sensor
{
  public:
    int Average();
    Sensor(int pin);
	int Min;
	int Max;
	int MinSave;
	int MaxSave;
	int MinSec;
	int MaxSec;
	int Value;
  private:
    int _pin;
};

#endif
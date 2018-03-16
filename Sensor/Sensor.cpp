#include "Arduino.h"
#include "Sensor.h"

Sensor::Sensor(int pin)
{
  pinMode(pin, INPUT);
  _pin = pin;
}

int Sensor::Average()
{
long suma=0;
for(int i=0;i<20;i++)
{
  suma=suma+analogRead(_pin);
}   
  return(suma/20);
}
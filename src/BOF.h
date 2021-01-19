// BOF.h

#ifndef _BOF_h
#define _BOF_h

#include "Arduino.h"
  
class BOF
{
 protected:
	 byte _pin;
	 bool _etat;
	 unsigned long _storedTime;
	 void switchOnOff();
	 void firstTimeBling();
	 unsigned int _onDuration;
	 unsigned int _offDuration;

 public:
	 BOF();
	 BOF(byte R_pin);

	 void begin();
	 void on();
	 void off();
	 
	 void bling(unsigned int onDuration, unsigned int offDuration);

	 void process(); 

	 
};

#endif

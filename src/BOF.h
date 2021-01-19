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
	 float _elapsedTime;
	 unsigned int _BPM;
	 float _onDuration;
	 float _offDuration;
	 bool _isEnable;
	 void switchOnOff();

 public:
	 BOF();
	 BOF(byte R_pin);

	 void begin();
	 void BPM(unsigned int varBPM=1);
	 
	 void on();
	 void off();
	 
	 void bling(float onDuration, float offDuration);
	 
	 void process();
	 void isDisable();
	 void isEnable();
	 void isPause();

	 
};

#endif

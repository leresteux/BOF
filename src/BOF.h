// BOF.h

#ifndef _BOF_h
#define _BOF_h

#include "Arduino.h"
  
class BOF
{
 protected:
	 byte _pin;
	 bool _isActivated;
	 unsigned long _storedTime;
	 float _elapsedTime;
	 unsigned int _BPM;
	 float _onDuration;
	 float _offDuration;
	 bool _isEnabled;
	 void switchOnOff();
	 float _oriOffDuration;
	 bool _fadeIsRunning;
	 float _varFade;

 public:
	 BOF();
	 BOF(byte R_pin);

	 void begin();
	 void BPM(unsigned int varBPM=1);
	 
	 void on();
	 void off();
	 
	 void bling(float onDuration, float offDuration);
	 void fade(float varFade);
	 void process();
	 void isDisable();
	 void isEnabled();
	 void isPause();

	 
};

#endif

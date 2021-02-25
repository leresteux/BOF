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
	 unsigned long _elapsedTime;
	 unsigned int _BPM;
	 float _onDuration;
	 float _offDurationAfter;
	 float _offDurationBefore;
	 bool _isEnabled;
	 void switchOnOff();
	 float _oriOffDurationBefore;
	 bool _fadeIsRunning;
	 float _varFade;
	 byte _blingState;

 public:
	 BOF();
	 BOF(byte R_pin);

	 void begin();
	 void BPM(unsigned int varBPM=1);
	 
	 void on();
	 void off();
	 
	 void bling(float offDurationBefore, float onDuration, float offDurationAfter=0);
	 void fade(float varFade);
	 void process();
	 void isDisable();
	 void isEnabled();
	 void isPause();

	 
};

#endif

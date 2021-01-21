#include "BOF.h"

BOF::BOF() {}

BOF::BOF(byte R_pin) {
  _pin = R_pin;

}

void BOF::begin() {
  pinMode(_pin, OUTPUT);
  _etat = false;
  _storedTime = 0;
  _isEnable=true;
  _BPM=1;
  off();
}

void BOF::BPM(unsigned int varBPM=1) {
	_BPM=60000/varBPM;	
}

void BOF::on() {
  _etat = true;
  if (_isEnable){
  digitalWrite(_pin, LOW);
  }
}

void BOF::off() {
  _etat = false;
  if (_isEnable){
  digitalWrite(_pin, HIGH);
  }
}

void BOF::process() {
	if (_storedTime == 0) {
		_storedTime = millis();
	  }
	_elapsedTime = millis()-_storedTime;
		switchOnOff();
	}
  
void BOF::bling(float onDuration, float offDuration) {
	_onDuration = _BPM*onDuration;
	_offDuration = _BPM*offDuration;
	_oriOffDuration = _offDuration;
}

void BOF::fade(float varFade) {
	if (_fadeIsRunning==false){
		_fadeIsRunning=true;
		_isEnable=true;
	}
	_varFade=varFade;
	if (varFade > 1 ){
		_offDuration=_offDuration/10;
	}
}		

void BOF::switchOnOff() {
  if (_elapsedTime >= _offDuration && _etat == false) {
		on();
		_storedTime = millis();
  }else if (_elapsedTime >= _onDuration && _etat == true) {
			if (_fadeIsRunning){
				_offDuration = _varFade*_offDuration;
				if (_offDuration <=1 || _offDuration>=_oriOffDuration ){
					_fadeIsRunning=false;
					_offDuration =_oriOffDuration;
				}
			}
			off();
			_storedTime = millis();
	}

}

void BOF::isEnable() {
  _isEnable=true;
}

void BOF::isDisable() {
  _isEnable=false;
  digitalWrite(_pin, HIGH);
}

void BOF::isPause() {
  if (_isEnable){
    isDisable();
  }else{
    isEnable();
  }
}

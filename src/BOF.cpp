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
  off();
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
   // firstTimeBling(); // a voir
  }
  switchOnOff();
}


void BOF::bling(unsigned int onDuration, unsigned int offDuration) {
  _offDuration = offDuration;
  _onDuration = onDuration;
}
void BOF::firstTimeBling() {

  
  if (_etat) {
    off();
  }
  else {
    on();
  }


}
void BOF::switchOnOff() {
  if ((millis() - _storedTime) >= _offDuration && _etat == false) {
    on();
    _storedTime = millis();
  }
  else if ((millis() - _storedTime) >= _onDuration && _etat == true) {
    off();
    _storedTime = millis();
  }

}

void BOF::isEnable() {
  _isEnable=true;
}

void BOF::isDisable() {
	off();
  _isEnable=false;
}

void BOF::isPause() {
  if (_isEnable){
    isEnable();
  }else{
    isDisable();
  }
}

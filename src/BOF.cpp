#include "BOF.h"

BOF::BOF() {}

BOF::BOF(byte R_pin) {
  _pin = R_pin;

}

void BOF::begin() {
  pinMode(_pin, OUTPUT);
  _etat = false;
  _storedTime = 0;
  _firstTimeBling = true;
  off();
}

void BOF::on() {
  _etat = true;
  digitalWrite(_pin, LOW);
}

void BOF::off() {
  _etat = false;
  digitalWrite(_pin, HIGH);
}


void BOF::process() {
  if (_firstTimeBling == true) {
    firstTimeBling();
  }
  switchOnOff();
}


void BOF::bling(unsigned int onDuration, unsigned int offDuration) {
  _offDuration = offDuration;
  _onDuration = onDuration;
}
void BOF::firstTimeBling() {

  _storedTime = millis();
  _firstTimeBling = false;

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
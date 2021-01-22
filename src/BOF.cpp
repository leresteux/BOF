#include "BOF.h"

BOF::BOF() {}

BOF::BOF(byte R_pin) {
  _pin = R_pin;

}
////////
// fonctions publiques
////////
// regle la pin attribué au relais et les varaibles au demarrage. A mettre dans Set up 
void BOF::begin() {
  pinMode(_pin, OUTPUT);
  _isActivated = false;
  _storedTime = 0;
  _isEnabled=true;
  _BPM=1;
  off();
}
/////
// "allume "le relais
void BOF::on() {
  _isActivated = true;
  if (_isEnabled){
  digitalWrite(_pin, LOW);
  }
}
/////
//"eteind" le relais
void BOF::off() {
  _isActivated = false;
  if (_isEnabled){
  digitalWrite(_pin, HIGH);
  }
}
/////
// doit être appeler regulierement (dans void loop) pour appliquer la librairie BOF
void BOF::process() {
	if (_storedTime == 0) {
		_storedTime = millis();
	  }
	_elapsedTime = millis()-_storedTime;
		switchOnOff();
	}
/////
// active le relais (par défaut)
void BOF::isEnabled() {
  _isEnabled=true;
}
/////
//desactive le relais
void BOF::isDisable() {
  _isEnabled=false;
  digitalWrite(_pin, HIGH);
}
/////
// active ou desactive le relais en fonction de l'etat 
void BOF::isPause() {
  if (_isEnabled){
    isDisable();
  }else{
    isEnabled();
  }
}
/////
// fait passer le relais d'un etat on à off en boucle ( si appeler par void process)
// float onDuration est indiqué en milliseconde et correspond à la durée en possition on du relais
// idem pour float offDuration
//les var onDuration et offDuration peuvent être introduites en Beat Par Minute si la fonction BPM a ete appeler au par avant 
// voir exemple beat_maker2
void BOF::bling(float onDuration, float offDuration) {
	_onDuration = _BPM*onDuration;
	_offDuration = _BPM*offDuration;
	_oriOffDuration = _offDuration;
}
/////
// permet de regler void bling en BPM
void BOF::BPM(unsigned int varBPM=1) {
	_BPM=60000/varBPM;	
}
/////
// créer un effet 
// fadein si la valeur de varFade est comprise entre 1 et 0 (idéal etant 0.8 par exemple) 
//fadein si la valeur de varFade est > 1 (idéal etant 1.2 par exemple)
void BOF::fade(float varFade) {
	if (_fadeIsRunning==false){
		_fadeIsRunning=true;
		_isEnabled=true;
	}
	_varFade=varFade;
	if (varFade > 1 ){
		_offDuration=_offDuration/10;
	}
}		

////////
//fonctions internes
////////
// calcule s'il doit allumer ou eteindre le relais
// voir void process
void BOF::switchOnOff() {
  if (_elapsedTime >= _offDuration && _isActivated == false) {
		on();
		_storedTime = millis();
  }else if (_elapsedTime >= _onDuration && _isActivated == true) {
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


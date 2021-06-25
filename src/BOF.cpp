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
  _blingState=0;
_modeBling=false;	
  _storedTime = millis();
  off();
}
/////
// "allume "le relais
void BOF::on() {
	_modeBling=false;
  _isActivated = true;
  if (_isEnabled){
  digitalWrite(_pin, HIGH);
  }
}
/////
//"eteind" le relais
void BOF::off() {
	_modeBling=false;
  _isActivated = false;
  if (_isEnabled){
  digitalWrite(_pin, LOW);
  }
}
/////
// doit être appeler regulierement (dans void loop) pour appliquer la librairie BOF
void BOF::process() {
	if (_storedTime == 0) {
		_storedTime = millis();
	  }
	  
	_elapsedTime = millis()-_storedTime;
	if (_modeBling==true){
		switchOnOff();
			    }
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
  digitalWrite(_pin, LOW);
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
void BOF::blingOff() {
	_modeBling=false;
  }


/////
// fait passer le relais d'un etat on à off en boucle ( si appeler par void process)
// peut etre ecrit : bling(offdurée,ondurée) ou bling(offdurée,ondurée,offdurée)
// float onDuration est indiqué en milliseconde et correspond à la durée en position on du relais
// idem pour float offDurationBefore et offDurationAfter 
//les variables peuvent être introduites en Beat Par Minute si la fonction BPM a ete appeler au par avant 
// voir exemple beat_maker2
void BOF::bling(float offDurationBefore, float onDuration, float offDurationAfter=0) {
	if(_modeBling==false){_modeBling=true;};
	_onDuration = _BPM*onDuration;

	_offDurationBefore = _BPM*offDurationBefore;
	_oriOffDurationBefore = _offDurationBefore;
	
	_offDurationAfter = _BPM*offDurationAfter;
	
	
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
		_offDurationBefore=_offDurationBefore/10;
	}
}		

////////
//fonctions internes
////////
// calcule s'il doit allumer ou eteindre le relais
// voir void process
void BOF::switchOnOff() {

	switch (_blingState) {
		// offBefore est en cours 
		case 0:
				if (_elapsedTime >= _offDurationBefore){
				//on
					 _isActivated = true;
  if (_isEnabled){
  digitalWrite(_pin, HIGH);
}
				_storedTime = millis();
				_blingState = 1; 

			}
			break;
		//on est en cours
		case 1:
		
			if (_elapsedTime >= _onDuration && _isActivated == true) {
			
				if (_fadeIsRunning){
					_offDurationBefore = _varFade*_offDurationBefore;
					_blingState = 0;
					if (_offDurationBefore <=1 || _offDurationBefore>=_oriOffDurationBefore ){
						_fadeIsRunning=false;
						_offDurationBefore =_oriOffDurationBefore;
					}
				}else{
					_blingState = 2;
					}
				//off
				  _isActivated = false;
  if (_isEnabled){
  digitalWrite(_pin, LOW);
}
				_storedTime = millis();
			
			}
			break;
		//offAfter est en cours
		case 2:
		
		if (_elapsedTime >= _offDurationAfter) {
			off();
			_storedTime = millis();
			_blingState = 0;
		}
		break;
	}
}

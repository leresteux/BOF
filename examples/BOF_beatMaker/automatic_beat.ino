/////
// must use with Chrono.h library
// Have fun !
// Ju'
////
#include <BOF.h>
#include <Chrono.h>

Chrono monchrono;
BOF monrelais1(3);
BOF monrelais2(4);
BOF monrelais3(5);
BOF monrelais4(6);

unsigned int nbrBPM = 120 ;
byte moment = 0;

void setup() {
  monrelais4.begin();
  monrelais3.begin();
  monrelais2.begin();
  monrelais1.begin();
  monrelais1.on();
  delay(1000);
  monrelais1.off();
  delay(1000);
  monrelais2.on();
  delay(1000);
  monrelais2.off();
  delay(1000);
  monrelais3.on();
  delay(1000);
  monrelais3.off();
  delay(1000);
  monrelais4.on();
  delay(1000);
  monrelais4.off();
  delay(1000);
  delay(10);
  monrelais1.BPM(nbrBPM);
  monrelais2.BPM(nbrBPM);
  monrelais3.BPM(nbrBPM);
  monrelais4.BPM(nbrBPM);
  monrelais2.isDisable();
  monrelais3.isDisable();
  monrelais4.isDisable();
  monrelais1.isDisable();
  delay(10);
  Serial.begin(9600);
  monrelais1.bling(1, 1, 0);
  monrelais1.fade(1.5);
  monchrono.restart();
}

void loop() {
  allProcess();


  if (monchrono.hasPassed(10000) && moment == 0) { 
    monchrono.restart();
    monrelais2.isEnabled();
    monrelais2.bling(1, 1, 2);
    moment++;
  };
  if (monchrono.hasPassed(20000) && moment == 1) { 
    monchrono.restart();
    monrelais3.isEnabled();
    monrelais3.bling(3, 1, 0);
    moment++;
  };

  if (monchrono.hasPassed(15000) && moment == 2) { 
    monchrono.restart();
    monrelais4.isEnabled();
    monrelais4.bling(7, 1, 0);
    moment++;
  };
  if (monchrono.hasPassed(20000) && moment == 3) { 
    monchrono.restart();
    monrelais3.isPause();
    moment++;
  };
  if (monchrono.hasPassed(10000) && moment == 4) { 
    monchrono.restart();
    monrelais1.isPause();
    moment++;
  };

  if (monchrono.hasPassed(10000) && moment == 5) { 
    monchrono.restart();
    monrelais1.isPause();
    moment++;
  };

  if (monchrono.hasPassed(10000) && moment == 6) { 
    monchrono.restart();
    monrelais2.isPause();
    moment++;
  };
  if (monchrono.hasPassed(30000) && moment == 7) { 
    monchrono.restart();
    monrelais2.isDisable();
    monrelais3.isDisable();
    monrelais4.isDisable();
    monrelais1.isDisable();
    moment++;
  };
}
void allProcess () {
  monrelais4.process();
  monrelais3.process();
  monrelais2.process();
  monrelais1.process();
}

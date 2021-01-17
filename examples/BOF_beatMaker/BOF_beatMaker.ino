#include <BOF.h>
// create a new relay object and attach it to a pin
BOF monrelais(3);
BOF monrelais1(4);

unsigned int beat;
unsigned int BPM = 180 ;
bool didIt=false;


void setup() {

  monrelais.begin();
  monrelais1.begin();

//test  
//on() and off() don't need to call with process();
  monrelais.on();
  delay(500);
  monrelais.off();
  delay(500);

  monrelais1.on();
  delay(500);
  monrelais1.off();
  delay(500);
  beat = 60000/BPM;

//def : monrelais.bling(unsigned int onDuration, unsigned int offDuration)
  monrelais.bling(beat, 3*beat);
  monrelais1.bling(beat, beat);
}

void loop() {

  delay(1);

  monrelais.process();
  monrelais1.process();
}
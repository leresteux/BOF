#include <BOF.h>

BOF monrelais1(3);
BOF monrelais2(4);
BOF monrelais3(5);
String incoming = "";

unsigned int BPM = 240 ;


void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  monrelais3.begin();
  monrelais2.begin();
  monrelais1.begin();

  monrelais1.BPM(BPM);
  monrelais2.BPM(BPM);
  monrelais3.BPM(BPM);


  //def : monrelais.bling(unsigned int onDuration, unsigned int offDuration)
  monrelais2.bling(1,3);
  monrelais3.bling(1, 1);
  monrelais1.bling(2, 2);
  delay(10);
  monrelais1.isDisable();
  monrelais2.isDisable();
}

void loop() {


  monrelais3.process();
  monrelais2.process();
  monrelais1.process();

  if (Serial.available() > 0) {

    incoming = Serial.readString() ;

    if (incoming.indexOf("1") >= 0 ) {
      monrelais1.isPause();
      incoming = "";
    }

    if (incoming.indexOf("2") >= 0) {
      monrelais2.isPause();
      incoming = "";
    }
    if (incoming.indexOf("3") >= 0) {
      monrelais3.isPause();
      incoming = "";
    }
  }
}

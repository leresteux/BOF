// Use Serial Monitor to control the relay
// Enter :
// a number (ex : "1") to play or pause a relay
// "BMP" to change BPM
// or use + and - to up or down BPM by 10
// "FADEIN" to fade-in a relay
// "FADEOUT" to fade-out a relay
/////
// Have fun !
// Ju'
////
#include <BOF.h>

BOF monrelais1(3);
BOF monrelais2(4);
BOF monrelais3(5);
String incoming = "";

bool readOK = false;

unsigned int BPM = 240 ;


void setup() {
  Serial.begin(115200); // opens serial port, sets data rate to 9600 bps
  Serial.setTimeout(10);
  monrelais3.begin();
  monrelais2.begin();
  monrelais1.begin();
  boot();
  delay(10);
  monrelais1.isDisable();
  monrelais2.isDisable();
  monrelais3.isDisable();
}

void loop() {

  allProcess ();

  if (Serial.available() > 0) {
    incoming = Serial.readString() ;
    Serial.println(incoming);
    serialForBMP();
    serialForPausse();
    serialForFade();

    incoming = "";
  }
}
void boot() {
  monrelais3.BPM(BPM);
  monrelais2.BPM(BPM);
  monrelais1.BPM(BPM);
  monrelais2.bling(1, 3);
  monrelais3.bling(1, 1);
  monrelais1.bling(2, 2);
}

void serialForBMP() {
  if (incoming.indexOf("+") >= 0) {
    BPM = BPM + 10;
    boot();
  }
  if (incoming.indexOf("-") >= 0) {
    BPM = BPM - 10;
    boot();
  }
  if (incoming.indexOf("BPM") >= 0 ) {
    Serial.print("CHANGE BPM : ");
    Serial.println("(by int number)");
    incoming = "";
    readOK = false;
    while (!readOK) {
      allProcess ();
      if (Serial.available() > 0) {
        incoming = Serial.readString();
        BPM = incoming.toInt();
        boot();
        readOK = true;
        allProcess();
      }
    }
    Serial.println(BPM);
    incoming = "";
    readOK = false;
  }
}

void serialForPausse() {

  if (incoming.indexOf("1") >= 0 ) {
    monrelais1.isPause();
  }
  if (incoming.indexOf("2") >= 0) {
    monrelais2.isPause();
  }
  if (incoming.indexOf("3") >= 0) {
    monrelais3.isPause();
  }
}

void serialForFade() {
  if (incoming.indexOf("FADEOUT") >= 0 ) {
    Serial.print("RELAY NUMBER : ");
    Serial.println("(by int number)");
    incoming = "";
    readOK = false;
    while (!readOK) {
      allProcess ();
      if (Serial.available() > 0) {
        incoming = Serial.readString();
        int R = incoming.toInt();
        switch (R) {
          case 1:
            monrelais1.fade(0.8);
            break;
          case 2:
            monrelais2.fade(0.8);
            break;
          case 3:
            monrelais3.fade(0.8);
            break;
          /*
            case 4:
            monrelais4.fade(0.8);
            break;
          */
          default:
            break;
        }
        
        Serial.print ("FADE-IN : ");
        Serial.println (R);
        readOK = true;
        incoming = "";
      }
    }
  }
  if (incoming.indexOf("FADEIN") >= 0 ) {
    Serial.print("RELAY NUMBER : ");
    Serial.println("(by int number)");
    incoming = "";
    readOK = false;
    while (!readOK) {
      allProcess ();
      if (Serial.available() > 0) {
        incoming = Serial.readString();
        int R = incoming.toInt();
        switch (R) {
          case 1:
            monrelais1.fade(1.2);
            break;
          case 2:
            monrelais2.fade(1.2);
            break;
          case 3:
            monrelais3.fade(1.2);
            break;
          /*
            case 4:
            monrelais4.fade(1.2);
            break;
          */
          default:
            break;
            
        }
        Serial.print ("FADE-IN : ");
        Serial.println (R);
        readOK = true;
        incoming = "";
      }
    }
  }
  readOK = false;
}
void allProcess () {
  monrelais3.process();
  monrelais2.process();
  monrelais1.process();
}

#include "Keyboard.h"

int inCh = 0;

void initSerials() {
#if 0
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Serial ready!");
#endif

  Serial1.begin(9600);
  while (!Serial1);
  Serial1.println("Serial1 ready!");
}

void setup() {
  initSerials();
  Keyboard.begin();
}

void loop() {
  if (Serial1.available() > 0) {
    inCh = Serial1.read();
#if 1
    switch (inCh) {
      case 13:
        Keyboard.write(KEY_RETURN);
        break;

      default:
        Keyboard.write((char)inCh);
    }
#else
    Keyboard.write((char)inCh);
    Serial.println(inCh, DEC);
#endif
  }
}

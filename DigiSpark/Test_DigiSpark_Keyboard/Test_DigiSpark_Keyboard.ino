#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.sendKeyStroke(0);
}

void loop() {
  DigiKeyboard.println("Hello Digispark!");
  DigiKeyboard.delay(5000);
}

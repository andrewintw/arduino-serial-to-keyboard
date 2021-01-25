#include <SoftSerial_INT0.h>
#include "DigiKeyboard.h"

#define P_RX    2               // Reception PIN (SoftSerial)
#define P_TX    1               // Transmition PIN (SoftSerial)

int inChar = 0;

SoftSerial uart(P_RX, P_TX);    // Software serial port for module

void setup()
{
  uart.begin(9600);
  DigiKeyboard.sendKeyStroke(0);
}

void loop()
{
  DigiKeyboard.update();

  if (uart.available()) {
    inChar = uart.read();
    if (inChar == 13) {
      uart.write('\n');
      DigiKeyboard.sendKeyStroke(KEY_ENTER);
    } else {
      uart.write(inChar);
      DigiKeyboard.print((char)inChar);
    }
  }

  DigiKeyboard.delay(10);
  //delay(100);
}

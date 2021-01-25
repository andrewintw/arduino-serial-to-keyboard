#include <SoftSerial_INT0.h>

#define P_RX    2               // Reception PIN (SoftSerial)
#define P_TX    1               // Transmition PIN (SoftSerial)

SoftSerial uart(P_RX, P_TX);    // Software serial port for module

void setup()
{
  uart.begin(9600);             // Initialize the serial port
}

void loop()
{
  // Basic Echo Test
  if (uart.available()) {
    uart.write(uart.read());
  }

  //delay(100);
}

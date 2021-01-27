
int inSByte = 0;

void setup() {
  Serial.begin(9600);   // USB Serial (CDC)
  Serial1.begin(9600);  // Real Serial (pin0 & pin1)

  while (!Serial);
  Serial.println("Serial ready");

  while (!Serial1);
  Serial1.println("Serial1 ready");
}

void passthroughTest() {
  if (Serial.available()) {
    Serial1.write(Serial.read());   // RX LED on (near pin7)
  }

  if (Serial1.available()) {
    Serial.write(Serial1.read());   // TX LED on (near pin14)
  }
}

void serialOutTest() {
  Serial.print("Lee");
  Serial.print(' ');

  Serial.write(84);     // T (84/54h)
  Serial.write(0x7a);   // z (122/7ah)
  Serial.write(117);    // u (117/75h)
  Serial.write(0x2d);   // - (45/2dh)
  Serial.write(84);     // T (84/54h)
  Serial.write(117);    // u (117/75h)
  Serial.write(110);    // n (110/6eh)
  Serial.write(0x67);   // g (103/67h)
  Serial.write(10);     // LF (10/ah)

  delay(1000);
}

void serial1OutTest() {
  Serial1.print("L.");
  Serial1.write(84);    // T (84/54h)
  Serial1.write(0x7a);  // z (122/7ah)
  Serial1.write(117);   // u (117/75h)
  Serial1.write(0x2d);  // - (45/2dh)
  Serial1.write(84);    // T (84/54h)
  Serial1.write(117);   // u (117/75h)
  Serial1.write(110);   // n (110/6eh)
  Serial1.write(0x67);  // g (103/67h)
  Serial1.write(10);    // LF (10/ah)

  delay(1000);
}

void serialToSerial1() {
  if (Serial.available() > 0) {
    inSByte = Serial.read();
    Serial1.print(millis());
    Serial1.print(":");
    //Serial1.println(inSByte);     // DEC
    Serial1.println((char)inSByte);
  }
}

void serial1ToSerial() {
  if (Serial1.available() > 0) {
    inSByte = Serial1.read();
    Serial.print(millis());
    Serial.print(":");
    //Serial1.println(inSByte);     // DEC
    Serial.println((char)inSByte);
  }
}

void loop() {
  //serialOutTest();
  //serial1OutTest();
  //serialToSerial1();
  //serial1ToSerial();
  passthroughTest();
}

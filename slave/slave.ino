#include <Wire.h>
char command;

int analogPin0 = A0;
int analogPin1 = A1;
int analogPin2 = A2;

void read_temperature() {
  // Read temperature as Celsius (the default)
  int t = analogRead(analogPin0);
  byte buf[2];
  buf[0] = highByte(t);
  buf[1] = lowByte(t);
  Wire.write(buf, 2);
}
void read_humidity() {
  // Read humidity
  int h = analogRead(analogPin1);
  byte buf[2];
  buf[0] = highByte(h);
  buf[1] = lowByte(h);
  Wire.write(buf, 2);
}

void read_pressure() {
  // Read atmospheric pressure
  int p = analogRead(analogPin2);
  byte buf[2];
  buf[0] = highByte(p);
  buf[1] = lowByte(p);
  Wire.write(buf, 2);
}

void setup() {
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  Wire.begin(23);
  Wire.onRequest(eventoSolicitud);
  Wire.onReceive(eventoRecepcion);
}

void loop() {
  delay(100);
}
void eventoRecepcion() {
  command  = Wire.read();
}
void eventoSolicitud() {

  if ( command == 'T' ) {
    read_temperature();
  }
  if ( command == 'H' ) {
    read_humidity();
  }
  if ( command == 'P' ) {
    read_pressure();
  }
}

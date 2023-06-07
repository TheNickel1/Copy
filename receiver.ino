#include <SPI.h>
#include "printf.h"
#include "RF24.h"

RF24 radio(7, 8);

uint8_t address[][6] = { "1Node", "2Node" };
bool radioNumber = 0;

struct DroneReceive {
  int R = 0;
  int P = 0;
  int Y = 0;
  int x = 0;
  int y = 0;
  int z = 0;
  bool iH = false;
  bool iS = false;
};

void setup() {
  Serial.begin(115200);

  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    while (1) {}
  }

  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(sizeof(DroneReceive));
  radio.openWritingPipe(address[radioNumber]);
  radio.openReadingPipe(1, address[!radioNumber]);

  radio.startListening();  
  Serial.println("start");
}

void loop() {
  if (radio.available()) {
    DroneReceive incoming;
    radio.read(&incoming, sizeof(incoming));
//    Serial.print(incoming.R);
//    Serial.print(", ");
//    Serial.print(incoming.P);
//    Serial.print(", ");
//    Serial.print(incoming.Y);
//    Serial.print(", ");
//    Serial.print(incoming.x);
//    Serial.print(", ");
//    Serial.print(incoming.y);
//    Serial.print(", ");
//    Serial.print(incoming.z);
    Serial.print(" INFO: ");
    Serial.print(incoming.iH);
    Serial.print("::");
    Serial.print(incoming.iS);
    Serial.println();
  }
}

#include <Arduino.h>
#include "bracer_control_panel.h"

BracerControlPanel* control_panel;

void setup() {
  control_panel = new BracerControlPanel();
  control_panel->setup();
}

void loop() {
  control_panel->updateComponents();
}


/*
String name = "LED";
String characteristic = "19B10001-E8F2-537E-4F6C-D104768A1214";
BracerBT* bluetooth;

void setup() {
  bluetooth = new BracerBT();
  bluetooth->init();

  while(!bluetooth->connectToPeripheral(name)) {
    Serial.println("Trying Initial Connection...");
    delay(500);
  }

  bluetooth->setCharacteristic(name, characteristic);
}

void loop() {
  while(!bluetooth->isPeripheralConnected(name)) {
    Serial.println("Connecting...");
    bluetooth->connectToPeripheral(name);
    bluetooth->setCharacteristic(name, characteristic);
    delay(500);
  }
  bluetooth->sendDataTo(name, 1);
  delay(500);
  bluetooth->sendDataTo(name, 0);
  delay(500);
}
*/
#pragma once

#include <ArduinoBLE.h>
#include <String>
#include "peripheral.h"
/*
//TODO: There may be some slight issues:
1) I am not sure if while we are scanning (assuming one of the other devices got dc'ed) that we will be able to still transmit data to the still connected devices
2) I am not sure what blocking issues we may run int
3) We need to make sure, after initializing this bridge, we have a 1 second delay to allow the module to properly start

*/
/*
struct Peripheral {
  String name;
  BLEDevice device;
  BLECharacteristic characteristic;
};
*/

class BtBridge {
public:
  BtBridge();
  void init();
  bool connectToPeripheral(String name);
  bool isPeripheralConnected(String name);
  void removePeripheral(String name);

  void sendDataTo(String name, byte* data, size_t length);
  byte getDataFrom(String name);
  void printPeripherals();

private:
  static constexpr int PERIPHERAL_COUNT = 2;
  Peripheral peripherals[PERIPHERAL_COUNT];
  static constexpr int BUFFER_SIZE = 10;
};
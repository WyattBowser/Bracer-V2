
#pragma once
#include <Arduino.h>
#include <ArduinoBLE.h>

class Peripheral {
public:
  Peripheral();
  static Peripheral createPeripheral(BLEDevice device_);

  String getName() { return name; }
  void setName(String name_) { name = name_; }

  String name = "none";
  BLEDevice device;
  BLECharacteristic characteristic;

private:
  Peripheral(String name_, BLEDevice device_, BLECharacteristic characteristic_);
};

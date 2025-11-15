#include "peripheral.h"

Peripheral::Peripheral() {}

Peripheral::Peripheral(String name_, BLEDevice device_, BLECharacteristic characteristic_) :
  name(name_), device(device_), characteristic(characteristic_) {
          Serial.print("Given Characteristic UUID: ");
          Serial.println(characteristic_.uuid());
          Serial.print("Object Characteristic UUID: ");
          Serial.println(characteristic.uuid());
  }

Peripheral Peripheral::createPeripheral(BLEDevice device_) {
  String name_ = device_.localName();
  if (name_ == "Hijack Jetpack") {
    if (!device_.discoverAttributes()) {
      Serial.println("Unable to discover attributes of jetpack");
      return Peripheral();
    }
    Serial.println("Device Characteristic list of Jetpack is: ");
    for(int i = 0; i < device_.characteristicCount(); i ++) {
      Serial.print("\t");
      Serial.println(device_.characteristic(i).uuid());
    }
    BLECharacteristic characteristic_ = device_.characteristic("6969");
    if (!characteristic_) {
      Serial.println("This device does not have the correct characteristic!");
      return Peripheral();
    }
    return Peripheral(name_, device_, characteristic_);
  }

  if (name_ == "Hijack Helmet") {
    if (!device_.discoverAttributes()) {
      Serial.println("Unable to discover attributes of helmet");
      return Peripheral();
    }
    Serial.println("Device Characteristic list of Helmet is: ");
    for(int i = 0; i < device_.characteristicCount(); i ++) {
      Serial.print("\t");
      Serial.println(device_.characteristic(i).uuid());
    }
    BLECharacteristic characteristic_ = device_.characteristic("6969");
    if (!characteristic_) {
      Serial.println("This device does not have the correct characteristic!");
      return Peripheral();
    }
    return Peripheral(name_, device_, characteristic_);
  }

  return Peripheral();
}
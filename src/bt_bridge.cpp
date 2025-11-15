#include "bt_bridge.h"

BtBridge::BtBridge() {}

void BtBridge::init() {
  BLE.begin();
  delay(250);

  //Fill our peripherals array with "none" peripherals
  for(int i = 0; i < PERIPHERAL_COUNT; i++) {
    Peripheral empty;
    empty.name = "none";
    peripherals[i] = empty;
  }
}

bool BtBridge::connectToPeripheral(String name) {
  BLE.scanForName(name);
  BLEDevice found_peripheral = BLE.available();

  if(found_peripheral) {
    BLE.stopScan();

    Serial.println("Found Peripheral!");
    bool connected = found_peripheral.connect();
    if (connected) {
      Serial.println("Connected to " + name);
    } else {
      Serial.println("Connection to " + name + " failed!");
      return false;
    }

    bool discovered_attributes = found_peripheral.discoverAttributes();

    if (discovered_attributes) { Serial.println("Got Attributes"); }
    else {
      Serial.println("CANT GET ATTRIBUTES"); 
      found_peripheral.disconnect(); 
      return false;
    }


    //Save the peripheral
    for(int i = 0; i < PERIPHERAL_COUNT; i++) {
      Serial.println("Adding " + name + " to list of peripherals");
      if(peripherals[i].name == "none") {
        Peripheral new_peripheral = Peripheral::createPeripheral(found_peripheral);
        if (new_peripheral.getName() == "none") {
          return false;
        }
        Serial.println("Found an empty slot. Adding...");
        peripherals[i] = new_peripheral;
        printPeripherals();
        break;
      }
    }
    return true;
  }
  return false;
}

bool BtBridge::isPeripheralConnected(String name) {
  for(int i = 0; i < PERIPHERAL_COUNT; i++) {
    if(peripherals[i].name == name) {
      if(!peripherals[i].device.connected()) {
        Serial.println(name + " is no longer connected. Removing from list.");
        peripherals[i].name = "none";
        return false;
      }
      return true;
    }
  }
  return false;
}

void BtBridge::removePeripheral(String name) {
    for(int i = 0; i < PERIPHERAL_COUNT; i++) {
    if(peripherals[i].name == name) {
      peripherals[i].name = "none";
      peripherals[i].device.disconnect();
      return;
    }
  }
}

void BtBridge::sendDataTo(String name, byte* data, size_t length) {
  Serial.print("Looking for peripheral: ");
  Serial.println(name);
  printPeripherals();
  for(int i = 0 ; i < PERIPHERAL_COUNT; i++) {
    if(peripherals[i].name == name) {
      Serial.print("Found peripheral, sending Data: ");
      for (int i = 0; i < length; i++) {
        Serial.print(data[i]);
        Serial.print(" ");
      }
      Serial.println();
      peripherals[i].characteristic.writeValue(data, length);
    }
  }
}

byte BtBridge::getDataFrom(String name) {
  for(int i = 0 ; i < PERIPHERAL_COUNT; i++) {
    if(peripherals[i].name == name) {
      byte value;
      peripherals[i].characteristic.readValue(value);
      return value;
    }
  }
  return 0x00;
}

void BtBridge::printPeripherals() {
  Serial.println("LIST OF PERIPHERALS===========");
  for (int i = 0; i < PERIPHERAL_COUNT; i++) {
    if (peripherals[i].name == "none") {continue;}
    Serial.println("Name: " + peripherals[i].name);
    Serial.print("Characteristic: ");
    Serial.println(peripherals[i].characteristic.uuid());
  }
}
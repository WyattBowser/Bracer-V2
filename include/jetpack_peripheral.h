#pragma once
#include <Arduino.h>
#include <ArduinoBLE.h>
#include "jetpack_deps/common.h"
#include "jetpack_deps/bluetooth.h"

class JetpackPeripheral {
public:
  JetpackPeripheral();

  bool attach(BLEDevice device);
  void detach();
  bool isAttached() const { return attached_; }

  void update();
  JetpackState getState() const { return current_state_; }

private:
  BLEDevice device_;
  BLECharacteristic state_characteristic_;
  JetpackState current_state_ = JetpackState::DISARMED;
  bool attached_ = false;
};

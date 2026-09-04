#include "jetpack_peripheral.h"

JetpackPeripheral::JetpackPeripheral() {}

bool JetpackPeripheral::attach(BLEDevice device) {
  state_characteristic_ = device.characteristic(JETPACK_STATE_UUID);
  if (!state_characteristic_) {
    Serial.println("JetpackPeripheral: state characteristic not found");
    attached_ = false;
    return false;
  }

  device_ = device;
  if (state_characteristic_.canSubscribe()) {
    state_characteristic_.subscribe();
  }
  attached_ = true;
  return true;
}

void JetpackPeripheral::detach() {
  attached_ = false;
}

void JetpackPeripheral::update() {
  if (!attached_ || !device_.connected()) {
    attached_ = false;
    return;
  }

  int32_t raw_state = 0;
  if (state_characteristic_.readValue(raw_state)) {
    JetpackState new_state = static_cast<JetpackState>(raw_state);
    if (new_state != current_state_) {
      Serial.print("JetpackPeripheral: state changed ");
      Serial.print(toString(current_state_));
      Serial.print(" -> ");
      Serial.println(toString(new_state));
      current_state_ = new_state;
    }
  }
}

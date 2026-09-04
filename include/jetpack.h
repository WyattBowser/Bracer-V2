#pragma once
#include <Arduino.h>
#include "jetpack_deps/common.h"

enum JetpackStatus {
  CONNECTING,
  DISCONNECTED,
  STATE
};

class Jetpack {
public:
  Jetpack(){};
  JetpackState getState() { return current_state; }
  void setState(JetpackState state) { current_state = state; }

  String getStatus() { 
    if (current_status == STATE) {
      return toString(current_state);
    } else {
      if (current_status == DISCONNECTED) {
        return "D/C";
      }
      if (current_status == CONNECTING) {
        return "CONN...";
      }
    }
  }

  JetpackStatus getCurrentStatus() { return current_status; }
  void setStatus(JetpackStatus status) { current_status = status; }

private:
  JetpackState current_state = JetpackState::DISARMED;
  JetpackStatus current_status = DISCONNECTED;
};
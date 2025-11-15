#pragma once
#include <Arduino.h>


enum class JETPACK_STATE {
  LAUNCH,
  STOP,
  DONE,
  TEST_FOG,
  TEST_SOUND,
  TEST_LIGHTS,
  READY,
  DISCONNECTED,
  CONNECTING
};

class Jetpack {
public:
  Jetpack();
  String stateToString();
  JETPACK_STATE getState() { return current_state; }
  int8_t getStateAsInt8() { return (int8_t)current_state; }
  void setState(JETPACK_STATE cmd) { current_state = cmd; }

private:
  JETPACK_STATE current_state;
};
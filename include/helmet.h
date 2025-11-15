#pragma once
#include <Arduino.h>

enum class HelmetLedMode {
  OFF,
  SOLID,
  VOICE_ACTIVATED,
  COMBAT,
  FLIGHT,
  SLICING,
  END
};

enum class HelmetAccessoryState {
  DOWN,
  UP
};

enum class HelmetState {
  READY,
  TIMEDOUT,
  DISCONNECTED,
  CONNECTING,
  CONNECTED
};


class Helmet {
public:
  Helmet();
  void setState(HelmetState state);
  HelmetState getState();

  void setLedMode(HelmetLedMode mode);
  HelmetLedMode getLedMode() { return current_led_mode_; };

  void setAccessoryMode(HelmetAccessoryState state = HelmetAccessoryState::UP);
  void toggleAccessory();
  HelmetAccessoryState getAccessoryState() { return current_accessory_state_; }

  void setRGB(int r, int g, int b);
  int getRGB(String field);

  String translateHelmetMode();
  String translateHelmetStatus();
  String modeToString();

private:
  HelmetState current_state_ = HelmetState::DISCONNECTED;
  HelmetLedMode current_led_mode_ = HelmetLedMode::OFF;
  HelmetAccessoryState current_accessory_state_ = HelmetAccessoryState::UP;
  int rgb[3] = {0 ,0, 0};
};
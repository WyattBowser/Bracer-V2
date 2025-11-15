#include "helmet.h"

Helmet::Helmet(){};

void Helmet::setLedMode(HelmetLedMode mode) {
  current_led_mode_ = mode;
}

void Helmet::setRGB(int r, int g, int b) {
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
}

String Helmet::modeToString() {
  switch (current_led_mode_){
    case HelmetLedMode::OFF:
      return "X";
    case HelmetLedMode::SOLID:
      return "S";
    case HelmetLedMode::VOICE_ACTIVATED:
      return "V";
    case HelmetLedMode::COMBAT:
      return "C";
    case HelmetLedMode::FLIGHT:
      return "F";
    case HelmetLedMode::SLICING:
      return "H";
  }
  return "";
}

String Helmet::translateHelmetStatus() {
  switch (current_state_) {
    case HelmetState::CONNECTED:
      return "READY";
    case HelmetState::DISCONNECTED:
      return "D/C";
    default:
      return "?";
  }
}

int Helmet::getRGB(String field) {
  if (field == "red") {
    return rgb[0];
  }
  if (field == "green") {
    return rgb[1];
  }
  if (field == "blue") {
    return rgb[2];
  }
  return 0;
}

String Helmet::translateHelmetMode() {
  switch (current_led_mode_){
    case HelmetLedMode::OFF:
      return "X";
    case HelmetLedMode::SOLID:
      return "S";
    case HelmetLedMode::VOICE_ACTIVATED:
      return "V";
    case HelmetLedMode::COMBAT:
      return "C";
    case HelmetLedMode::FLIGHT:
      return "F";
    case HelmetLedMode::SLICING:
      return "H";
  }
  return "?";
}

void Helmet::setState(HelmetState state) {
  current_state_ = state;
}

HelmetState Helmet::getState() {
  return current_state_;
}

void Helmet::setAccessoryMode(HelmetAccessoryState state) {
  current_accessory_state_ = state;
}

void Helmet::toggleAccessory() {
  switch(current_accessory_state_) {
    case HelmetAccessoryState::UP:
      current_accessory_state_= HelmetAccessoryState::DOWN;
      break;
    case HelmetAccessoryState::DOWN:
      current_accessory_state_ = HelmetAccessoryState::UP;
      break;
  }
}
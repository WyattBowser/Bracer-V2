#include "temp_push_button.h"
#include <string>

TempPushButton::TempPushButton() {
  this->pin_ = PinIO();
}

TempPushButton::TempPushButton(std::string name) {
  this->name_ = name;
  this->pin_ = PinIO();
}

TempPushButton::TempPushButton(std::string name, pin_size_t pin, PinMode mode) {
  this->name_ = name;
  this->pin_ = PinIO(pin, mode, Digital_Pin_Read);
}

TempPushButton::~TempPushButton() {}

void TempPushButton::setState(bool state) {
  this->current_state_ = state;
}

bool TempPushButton::isPushed() {
  bool return_value = false;
  current_state_ = this->pin_.getInput();

  //This is operating under the assumption that the pin is in pullup
  //if pin is pulled up
  if (pin_.getPinMode() == INPUT_PULLUP) {
    if (current_state_ == false && last_state_ == true) {
      return_value = true;
    } 
  }
  //Pin is pulled down
  else {
    if (current_state_ == true && last_state_ == false) {
      return_value = true;
    }
  }
  last_state_ = current_state_;

  //Serial.print(name_.c_str());
  //Serial.print(" is pushed: ");
  //Serial.println(return_value);

  return return_value;
}
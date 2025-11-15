#pragma once
#include <api/Common.h>
#include <string>
#include "pin_io.h"

class TempPushButton{
public:
  TempPushButton();
  TempPushButton(std::string name);
  TempPushButton(std::string name, pin_size_t pin, PinMode);
  ~TempPushButton();
  
  void setState(bool state);
  bool isPushed();

private:
  std::string name_;
  bool current_state_;
  bool last_state_;
  PinIO pin_;
};
#pragma once
#include <string>
#include <api/Common.h>

#include "pin_io.h"

class Potentiometer {
public:
  Potentiometer();
  Potentiometer(std::string name);
  Potentiometer(std::string name, pin_size_t pin, PinMode mode);

  void setValue(uint8_t value);
  int getValue();

private:
  std::string name_;
  uint8_t value_;
  PinIO pin_;
};
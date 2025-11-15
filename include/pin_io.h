#pragma once
#include <api/Common.h>
#include <Arduino.h>

#ifndef READTYPE_ENUM
#define READTYPE_ENUM
  enum ReadType {
    Digital_Pin_Read,
    Analog_Pin_Read
  };
#endif


class PinIO {
public:

  PinIO();
  PinIO(pin_size_t pin);
  PinIO(pin_size_t pin, PinMode mode);
  PinIO(pin_size_t pin, PinMode mode, ReadType type);

  void setPin(pin_size_t pin);
  void setPinMode(PinMode mode);
  void setType(ReadType type);
  int getInput();
  int getPinMode();

private:
  pin_size_t pin_;
  PinMode mode_;
  ReadType read_type_;
};
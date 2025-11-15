#include "potentiometer.h"
#include <string>

Potentiometer::Potentiometer() {
  //Serial.println("[Potentiometer] Default Constructor");
}

Potentiometer::Potentiometer(std::string name) {
  //Serial.print("[Potentiometer] Constructing ");
  //Serial.print(name.c_str());
  //Serial.print(" Potentiometer");
  this->name_ = name;
  this->pin_ = PinIO();
}

Potentiometer::Potentiometer(std::string name, pin_size_t pin, PinMode mode) {
  this->name_ = name;
  this->pin_ = PinIO(pin, mode, Analog_Pin_Read);
}

void Potentiometer::setValue(uint8_t value) {
  this->value_ = value;
}

int Potentiometer::getValue() {
  return pin_.getInput();
}

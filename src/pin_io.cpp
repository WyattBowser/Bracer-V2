#include "pin_io.h"

PinIO::PinIO() {
  //Serial.println("[PinIO] Default PinIO constructed. Pin Unknown. pinMode never set. Unknown Read Type.");
};
PinIO::PinIO(pin_size_t pin) {
  this->pin_ = pin;
 //Serial.println("[PinIO] PinIO constructed with pin only. pinMode never set for this pin. Unknown Read Type.");
}

PinIO::PinIO(pin_size_t pin, PinMode mode) {
  this->pin_ = pin;
  this->mode_ = mode;
  pinMode(pin_, mode_);
  //Serial.println("[PinIO] PinIO constructed with pin and mode. pinMode set. Unknown Read Type.");
}

PinIO::PinIO(pin_size_t pin, PinMode mode, ReadType type) {
  this->pin_ = pin;
  this->mode_ = mode;
  pinMode(pin_, mode_);
  this->read_type_ = type;
  //Serial.println("[PinIO] PinIO constructed with pin and mode. pinMode set. Ready to be read.");
}

void PinIO::setPin(pin_size_t pin) {
  this->pin_ = pin;
}

void PinIO::setPinMode(PinMode mode) {
  this->mode_ = mode;
}

void PinIO::setType(ReadType type) {
  this->read_type_ = type;
}

int PinIO::getInput() {

  switch (read_type_) {
    case Digital_Pin_Read:
      return digitalRead(pin_);
    case Analog_Pin_Read:
      return analogRead(pin_);
    default:
      //Serial.print("[PinIO] Pin ");
      //Serial.print(pin_);
      //Serial.println(" could not read data off of a pin that is not set up to be read.");
      return -1;
  }
  return -1;
}

int PinIO::getPinMode() {
  return this->mode_;
}
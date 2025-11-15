#include "bracer_screen.h"

BracerScreen::BracerScreen():screen_(WIDTH, HEIGHT, &Wire, -1) {};


void BracerScreen::setup() {
  screen_.setTextColor(WHITE);
  screen_.setTextSize(this->text_size_);

  if(!screen_.begin(SSD1306_SWITCHCAPVCC, address_)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  clearDisplay();
  drawBitmap();
  display();
}

void BracerScreen::clearDisplay() {
  screen_.clearDisplay();
}

void BracerScreen::drawBitmap() {
  switch (current_background) {
    case MAIN:
      screen_.drawBitmap(0,0, MAIN_BACKGROUND_, WIDTH, HEIGHT, text_color_);
      break;
    case QR:
      screen_.drawBitmap(0,0, QR_BACKGROUND_, WIDTH, HEIGHT, text_color_);
      break;
  }
}

void BracerScreen::display() {
  screen_.display();
}

void BracerScreen::updateRectangle(DisplayRect rect, int value) {
  //Blank out rectangle
  screen_.fillRect(rect.x_pos, rect.y_pos, rect.width, rect.height, BLACK);
  //Write value
  screen_.setCursor(rect.x_pos, rect.y_pos + rect.value_y_pos_offset);
  screen_.print(value);
}

void BracerScreen::updateRectangle(DisplayRect rect, double value) {
  //Blank out rectangle
  screen_.fillRect(rect.x_pos, rect.y_pos, rect.width, rect.height, BLACK);
  //Write value
  screen_.setCursor(rect.x_pos, rect.y_pos + rect.value_y_pos_offset);
  screen_.print(value);
}

void BracerScreen::updateRectangle(DisplayRect rect, char value) {
  //Blank out rectangle
  screen_.fillRect(rect.x_pos, rect.y_pos, rect.width, rect.height, BLACK);
  //Write value
  screen_.setCursor(rect.x_pos, rect.y_pos + rect.value_y_pos_offset);
  screen_.print(value);
}

void BracerScreen::updateRectangle(DisplayRect rect, String value) {
  //Blank out rectangle
  screen_.fillRect(rect.x_pos, rect.y_pos, rect.width, rect.height, BLACK);
  //Write value
  screen_.setCursor(rect.x_pos, rect.y_pos + rect.value_y_pos_offset);
  screen_.print(value.c_str());
}

void BracerScreen::toggleBackground() {
  switch (current_background) {
    case MAIN:
      current_background = QR;
      break;
    case QR:
      current_background = MAIN;
      break;
  }
}

unsigned char* BracerScreen::currentBackground() {
  switch(current_background) {
    case MAIN:
      return MAIN_BACKGROUND_;
    case QR:
      return QR_BACKGROUND_;
  }
}
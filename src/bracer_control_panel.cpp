#include "bracer_control_panel.h"
//3 goes to 7
BracerControlPanel::BracerControlPanel() {
  pot = Potentiometer("RGB Potentiometer", A0, INPUT);
  big_button = TempPushButton("Big Button", 7, INPUT_PULLUP);
  top_button = TempPushButton("Top Button", 2, INPUT_PULLUP);
  mid_button = TempPushButton("Mid Button", 5, INPUT_PULLUP);
  bot_button = TempPushButton("Bot Button", 6, INPUT_PULLUP);
}

void BracerControlPanel::setup() {
  setupRectangles();
  screen_.setup();
  bluetooth_.init();
  setupJetpack();
  setupHelmet();
}

void BracerControlPanel::setupRectangles() {

  helmet_status_rect_.width = 20;
  helmet_status_rect_.height = 15;
  helmet_status_rect_.x_pos = 92;
  helmet_status_rect_.y_pos = 10;
  helmet_status_rect_.value_y_pos_offset = 0;

  jetpack_status_rect_.width = 20;
  jetpack_status_rect_.height = 15;
  jetpack_status_rect_.x_pos = 92;
  jetpack_status_rect_.y_pos = 28;
  jetpack_status_rect_.value_y_pos_offset = 0;

  helmet_mode_rect_.width = 13;
  helmet_mode_rect_.height = 8;
  helmet_mode_rect_.x_pos = 85;
  helmet_mode_rect_.y_pos = 47;
  helmet_mode_rect_.value_y_pos_offset = 0;

  red_rect_.width = 20;
  red_rect_.height = 8;
  red_rect_.x_pos = 52;
  red_rect_.y_pos = 39;
  red_rect_.value_y_pos_offset = 0;

  green_rect_.width = 20;
  green_rect_.height = 8;
  green_rect_.x_pos = 52;
  green_rect_.y_pos = 47;
  green_rect_.value_y_pos_offset = 0;

  blue_rect_.width = 20;
  blue_rect_.height = 8;
  blue_rect_.x_pos = 52;
  blue_rect_.y_pos = 55;
  blue_rect_.value_y_pos_offset = 0;
}

void BracerControlPanel::updateRGBValues() {
  int value = pot.getValue();
  value = int(value * 255 / 1023);

  if (value <= 42.5) {
    rgb[0] = 255;
    rgb[1] = value * 6;
    rgb[2] = 0;
   } else if ((value > 42.5) && (value <= 85)) {
    rgb[0] = 255 - (value - 43) * 6;
    rgb[1] = 255;
    rgb[2] = 0;
   } else if ((value > 85) && (value <= 127.5)) {
    rgb[0] = 0;
    rgb[1] = 255;
    rgb[2] = (value - 85) * 6;
   } else if ((value > 127.5) && (value <= 170)) {
    rgb[0] = 0;
    rgb[1] = 255 - (value - 127.5) * 6;
    rgb[2] = 255;
  } else if ((value > 170) && (value <= 212.5)) {
    rgb[0] = (value - 170) * 6;
    rgb[1] = 0;
    rgb[2] = 255;
  } else if ((value > 212.5) && (value <= 255)) {
    rgb[0] = 255;
    rgb[1] = 0;
    rgb[2] = 255 - (value - 212.5) * 6;
  }
}

void BracerControlPanel::updateComponents() {
  
  //Update connection state of helmet
  if(!bluetooth_.isPeripheralConnected(HELMET_NAME)) {
    if(!bluetooth_.connectToPeripheral(HELMET_NAME)) {
      helmet.setState(HelmetState::DISCONNECTED);
      bluetooth_.removePeripheral(HELMET_NAME);
    } else {
      helmet.setLedMode(HelmetLedMode::OFF);
    }
  } else if (helmet.getState() == HelmetState::DISCONNECTED){
    helmet.setState(HelmetState::CONNECTED);
  }

  updateHelmetObject();  //This will update the rgb values, helmet object and peripheral
  updateJetpackObject(); //This will update both the object and the peripheral

  //Update Screen
  updateScreen();
}

void BracerControlPanel::updateScreen() {

  /*
  if (top_button.isPushed()) {
    screen_.toggleBackground();
    return;
  }
*/

  if(millis() - last_update_ <= update_screen_timer) {return;} 

  screen_.clearDisplay();
  screen_.drawBitmap();

  switch(screen_.current_background) {
    case Background::MAIN: 
      screen_.updateRectangle(red_rect_, helmet.getRGB("red"));
      screen_.updateRectangle(green_rect_, helmet.getRGB("green"));
      screen_.updateRectangle(blue_rect_, helmet.getRGB("blue"));
      screen_.updateRectangle(helmet_status_rect_, helmet.translateHelmetStatus());
      screen_.updateRectangle(helmet_mode_rect_, helmet.translateHelmetMode());
      screen_.updateRectangle(jetpack_status_rect_, jetpack.stateToString());
      break;
    case Background::QR:
      break;
  }

  last_update_ = millis();
  screen_.display();
}

String BracerControlPanel::stringify(){
  return rgb[0] + " "; 
}

void BracerControlPanel::setupJetpack() {
  jetpack.setState(JETPACK_STATE::CONNECTING);
  if (!bluetooth_.connectToPeripheral(JETPACK_NAME)) {
    jetpack.setState(JETPACK_STATE::DISCONNECTED);
    return;
  }
  jetpack.setState(JETPACK_STATE::READY);
}

void BracerControlPanel::updateJetpackObject() {
  if (big_button.isPushed()) {
    switch (jetpack.getState()) {
      case JETPACK_STATE::LAUNCH:
        jetpack.setState(JETPACK_STATE::STOP);
        break;
      case JETPACK_STATE::READY:
        jetpack.setState(JETPACK_STATE::LAUNCH);
        break;
    } 
  }
  sendJetpackObject();
}

void BracerControlPanel::sendJetpackObject() {
  if(!bluetooth_.isPeripheralConnected(JETPACK_NAME)) {
    if(!bluetooth_.connectToPeripheral(JETPACK_NAME)) {
      jetpack.setState(JETPACK_STATE::DISCONNECTED);
      last_jetpack_state = jetpack.getState();
      return;
    } else {
      jetpack.setState(JETPACK_STATE::STOP);
    }
  } 
  
  if (jetpack.getState() == JETPACK_STATE::STOP) {
    jetpack.setState(JETPACK_STATE::READY);
  }
  
  if (jetpack.getState() != last_jetpack_state) {
    Serial.println("State changed");
    if (!bluetooth_.isPeripheralConnected(JETPACK_NAME)) {
      bluetooth_.removePeripheral(JETPACK_NAME);
      if(!bluetooth_.connectToPeripheral(JETPACK_NAME)) {
        jetpack.setState(JETPACK_STATE::DISCONNECTED);
        return;
      }
    }

    byte data[1] = {(uint8_t)jetpack.getState()};

    bluetooth_.sendDataTo(JETPACK_NAME, data, 1);
    last_jetpack_state = jetpack.getState();
    
  }
}

void BracerControlPanel::setupHelmet() {
  helmet.setState(HelmetState::CONNECTING);
  if (!bluetooth_.connectToPeripheral(HELMET_NAME)) {
    helmet.setState(HelmetState::DISCONNECTED);
    return;
  }
  helmet.setState(HelmetState::CONNECTED);
  helmet.setLedMode(HelmetLedMode::OFF);
}

void BracerControlPanel::updateHelmetObject() {
  if(top_button.isPushed()) {
    if (helmet.getAccessoryState() == HelmetAccessoryState::DOWN)
    {
      helmet.setAccessoryMode(HelmetAccessoryState::UP);
      helmet.setLedMode(HelmetLedMode::OFF);
    } else {
      helmet.setAccessoryMode(HelmetAccessoryState::DOWN);
      helmet.setLedMode(HelmetLedMode::SOLID);
    }
    sendHelmetObject();
  }
  if(mid_button.isPushed()) {
    sendHelmetObject();
  }
  if (bot_button.isPushed()) {
    int modeInt = (int)helmet.getLedMode();
    modeInt++;
    if(modeInt == (int)HelmetLedMode::END) { modeInt = 0; }
    helmet.setLedMode((HelmetLedMode)modeInt);
  }

  updateRGBValues();
  helmet.setRGB(rgb[0], rgb[1], rgb[2]);
}

void BracerControlPanel::sendHelmetObject() { 
  byte data_to_send[5];
  data_to_send[0] = (char)helmet.getLedMode();
  data_to_send[1] = (char)helmet.getAccessoryState();
  data_to_send[2] = helmet.getRGB("red");
  data_to_send[3] = helmet.getRGB("green");
  data_to_send[4] = helmet.getRGB("blue");
                     
  //Serial.print("data_to_send: ");
  //Serial.println(data_to_send);
  bluetooth_.sendDataTo(HELMET_NAME, data_to_send, 5);
}
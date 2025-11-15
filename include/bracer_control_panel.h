#pragma once
#include<vector>

#include "bracer_screen.h"
#include "temp_push_button.h"
#include "potentiometer.h"
#include "helmet.h"
#include "bt_bridge.h"
#include "jetpack.h"


class BracerControlPanel {

public:

  //Control Panel Specific
  BracerControlPanel();
  void setup();
  void updateComponents(); 
  void updateRGBValues();
  String stringify();

  //Bluetooth Stuff

  //Screen Stuff
  void setupRectangles();
  void setScreen(Adafruit_SSD1306* screen);
  void updateScreen();

  //Helmet Stuff
  void setupHelmet();
  void updateHelmetObject();
  void sendHelmetObject();

  //Jetpack Stuff
  void setupJetpack();
  void updateJetpackObject();
  void sendJetpackObject();
  String jetpackCmdToString(JETPACK_STATE cmd);
  
private:

  //Screen stuff
  BracerScreen screen_;
  DisplayRect helmet_mode_rect_;
  DisplayRect helmet_status_rect_;
  DisplayRect jetpack_status_rect_;
  DisplayRect red_rect_;
  DisplayRect blue_rect_;
  DisplayRect green_rect_;

  //Bluetooth stuff
  BtBridge bluetooth_;
  String CONNECTING = "Connecting";
  String CON_FAILED = "Connection Failed";
  String CON_LOST = "Connection Lost";
  String CONNECTED = "Connected";
  String READY = "Ready";


  //User Input stuff
  Potentiometer pot;
  TempPushButton top_button;
  TempPushButton mid_button;
  TempPushButton bot_button;
  TempPushButton big_button;

  int rgb[3] = {0, 0, 0};

  //States
  Jetpack jetpack;
  JETPACK_STATE last_jetpack_state = JETPACK_STATE::DISCONNECTED;
  String JETPACK_NAME = "Hijack Jetpack";
  String JETPACK_CHAR = "Jetpack Control";

  Helmet helmet;
  HelmetState last_helmet_mode = HelmetState::DISCONNECTED;
  String HELMET_NAME = "Hijack Helmet";
  String HELMET_CHAR = "Helmet Control";


  unsigned long last_update_ = 0;
  unsigned long update_screen_timer = 100;
};
#include "jetpack.h"

Jetpack::Jetpack() {}

String Jetpack::stateToString()  {
  switch(current_state){
    case JETPACK_STATE::LAUNCH:
      return "LAUNCH";
    case JETPACK_STATE::STOP:
      return "STOP";
    case JETPACK_STATE::DONE:
      return "DONE";
    case JETPACK_STATE::TEST_FOG:
      return "FOG";
    case JETPACK_STATE::TEST_SOUND:
      return "SOUND";
    case JETPACK_STATE::TEST_LIGHTS:
      return "LIGHTS";
    case JETPACK_STATE::READY:
      return "READY";
    case JETPACK_STATE::DISCONNECTED:
      return "D/C";
    case JETPACK_STATE::CONNECTING:
      return "CNTING";
    default:
      return "?";
  }
  return "?";
}
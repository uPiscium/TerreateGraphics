#ifndef __TERREATE_GRAPHICS_JOYSTICK_HPP__
#define __TERREATE_GRAPHICS_JOYSTICK_HPP__

#include "TerreateCore/defines.hpp"
#include "defines.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
using namespace TerreateGraphics::Core;
using namespace TerreateCore::Math;

void JoystickCallback(int id, int event);

struct JoystickAxisState {
  vec2 leftStick = vec2(0.0f);
  vec2 rightStick = vec2(0.0f);
  Float leftTrigger = 0.0f;
  Float rightTrigger = 0.0f;
};

struct JoystickButtonState {
  Bool a = false;
  Bool b = false;
  Bool x = false;
  Bool y = false;
  Bool cross = false;
  Bool circle = false;
  Bool square = false;
  Bool triangle = false;
  Bool leftBumper = false;
  Bool rightBumper = false;
  Bool back = false;
  Bool start = false;
  Bool guide = false;
  Bool leftThumb = false;
  Bool rightThumb = false;
  Bool dpadUp = false;
  Bool dpadRight = false;
  Bool dpadDown = false;
  Bool dpadLeft = false;
};

struct JoystickHatState {
  Bool up = false;
  Bool right = false;
  Bool down = false;
  Bool left = false;
};

class Joystick : public TerreateObjectBase {
private:
  JoystickID mJoystickId = JoystickID::NONE;

private:
  static Joystick sJoysticks[(Uint const)JoystickID::LAST + 1];

public:
  Joystick() = default;
  Joystick(JoystickID const &id) : mJoystickId(id) {}
  ~Joystick() = default;

  JoystickID const &GetJoystickId() const { return mJoystickId; }
  JoystickAxisState AcquireAxisState() const;
  JoystickButtonState AcquireButtonState() const;
  JoystickHatState AcquireHatState() const;

  Bool IsGamepad() const { return glfwJoystickIsGamepad((int)mJoystickId); }
  Bool IsConnected() const { return glfwJoystickPresent((int)mJoystickId); }

public:
  static Joystick const &GetJoystick(JoystickID const &id) {
    return sJoysticks[(Uint const)id];
  }
  static void SetJoystick(JoystickID const &id) {
    sJoysticks[(Uint const)id] = Joystick(id);
  }
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_JOYSTICK_HPP__

#ifndef __TERREATE_GRAPHICS_JOYSTICK_HPP__
#define __TERREATE_GRAPHICS_JOYSTICK_HPP__

#include "TerreateCore/defines.hpp"
#include "defines.hpp"

namespace TerreateGraphics::Core {
using namespace TerreateGraphics::Defines;
using namespace TerreateGraphics::Core;
using namespace TerreateCore::Math;

// GLFW joystick callback
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
  /*
   * @brief: Joystick is a class that represents a joystick.
   */
  Joystick() = default;
  /*
   * @brief: Joystick is a class that represents a joystick.
   * @param: id: the id of the joystick
   */
  Joystick(JoystickID const &id) : mJoystickId(id) {}
  ~Joystick() = default;

  /*
   * @brief: Get the id of the joystick
   * @return: the id of the joystick
   */
  JoystickID const &GetJoystickId() const { return mJoystickId; }
  /*
   * @brief: Acquire the state of the joystick axis
   * @return: the state of the joystick axis
   */
  JoystickAxisState AcquireAxisState() const;
  /*
   * @brief: Acquire the state of the joystick buttons
   * @return: the state of the joystick buttons
   */
  JoystickButtonState AcquireButtonState() const;
  /*
   * @brief: Acquire the state of the joystick hat
   * @return: the state of the joystick hat
   */
  JoystickHatState AcquireHatState() const;

  /*
   * @brief: Check if the joystick is a gamepad
   * @return: true if the joystick is a gamepad, false otherwise
   */
  Bool IsGamepad() const { return glfwJoystickIsGamepad((int)mJoystickId); }
  /*
   * @brief: Check if the joystick is connected
   * @return: true if the joystick is connected, false otherwise
   */
  Bool IsConnected() const { return glfwJoystickPresent((int)mJoystickId); }

public:
  /*
   * @brief: Get the joystick with the given id
   * @param: id: the id of the joystick
   * @return: the joystick with the given id
   */
  static Joystick const &GetJoystick(JoystickID const &id) {
    return sJoysticks[(Uint const)id];
  }
  /*
   * @brief: Set the joystick with the given id
   * @param: id: the id of the joystick
   */
  static void SetJoystick(JoystickID const &id) {
    sJoysticks[(Uint const)id] = Joystick(id);
  }
};
} // namespace TerreateGraphics::Core

#endif // __TERREATE_GRAPHICS_JOYSTICK_HPP__

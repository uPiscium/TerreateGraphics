#pragma once
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

// Defines
#ifdef GEOFRAME_IGNORE_EXCEPTIONS
#define M_GEO_THROW(exception, message)                                        \
  std::cerr << __FILE__ << ":" << __LINE__ << " " << message << std::endl;
#else
#define M_GEO_THROW(exception, message)                                        \
  std::cerr << __FILE__ << ":" << __LINE__ << " " << message << std::endl;     \
  throw exception(message)
#endif // GEOFRAME_IGNORE_EXCEPTIONS

#define M_DISABLE_COPY_AND_ASSIGN(Type)                                        \
  Type(const Type &) = delete;                                                 \
  Type &operator=(const Type &) = delete

#ifdef __linux__
#define M_MEMCPY(dest, src, size) memcpy(dest, src, size)
#define M_MEMCMP(dest, src, size) memcmp(dest, src, size)
#else
#define M_MEMCPY(dest, src, size) std::memcpy(dest, src, size)
#define M_MEMCMP(dest, src, size) std::memcmp(dest, src, size)
#endif // __linux__

#define D_GLAD <glad/gl.h>
#define D_GLFW <GLFW/glfw3.h>

#ifndef D_HALF_WIDTH_SPACE
#define D_HALF_WIDTH_SPACE 32
#endif // D_HALF_WIDTH_SPACE
#ifndef D_FULL_WIDTH_SPACE
#define D_FULL_WIDTH_SPACE 32306
#endif // D_FULL_WIDTH_SPACE
#define D_MAX_COLOR_ATTACHMENT 32

#include D_GLAD
#include D_GLFW
#include "exceptions.hpp"

namespace GeoFrame {
// Typedefs
template <typename S, typename T> using Map = std::unordered_map<S, T>;
template <typename T> using Pair = std::pair<T, T>;
template <typename T> using Set = std::unordered_set<T>;
template <typename T> using Vec = std::vector<T>;
using ID = unsigned;
using Index = unsigned long long;
using Str = std::string;
using WStr = std::wstring;

using ErrorCallback = void (*)(int errorCode, char const *description);
using MonitorCallback = void (*)(GLFWmonitor *monitor, int event);
using JoystickCallback = void (*)(int joystickID, int event);

template <typename Derived, typename Base>
concept extends = std::derived_from<Derived, Base>;

struct Modifier {
public:
  bool shift = false;
  bool control = false;
  bool alt = false;
  bool numLock = false;

public:
  Modifier(int mods_)
      : shift(mods_ & GLFW_MOD_SHIFT), control(mods_ & GLFW_MOD_CONTROL),
        alt(mods_ & GLFW_MOD_ALT), numLock(mods_ & GLFW_MOD_SUPER) {}
};

struct Key {
public:
  int key = 0;
  int scancode = 0;
  int action = 0;
  Modifier mods = 0;

public:
  Key(int key_, int scancode_, int action_, int mods_)
      : key(key_), scancode(scancode_), action(action_), mods(mods_) {}
};

class SingletonFinalizer {
public:
  using Finalizer = void (*)();

public:
  static void AddFinalizer(Finalizer finalizer);
  static void Finalize();
};

/*
 * @brief: This class is used to create a singleton.
 * @param: T: class to be created as a singleton
 */
template <typename T> class Singleton final {
private:
  static T *sInstance;
  static std::once_flag sCallFlag;

private:
  /*
   * @brief: Constructor function for Singleton. This function is private
   * because Singleton should only be created by Singleton::AquireInstance().
   */
  static void CreateInstance() {
    sInstance = new T();
    SingletonFinalizer::AddFinalizer(&Delete);
  }
  /*
   * @brief: Destructor function for Singleton. This function is private because
   * Singleton should only be destroyed by SingletonFinalizer::Finalize().
   */
  static void Delete() {
    delete sInstance;
    sInstance = nullptr;
  }

public:
  /*
   * @brief: Aquires the singleton instance.
   * @return: singleton instance
   */
  static T &AquireInstance() {
    std::call_once(sCallFlag, &CreateInstance);
    if (sInstance == nullptr) {
      M_GEO_THROW(KernelError, "Failed to create singleton instance.");
    }
    return *sInstance;
  }
};

template <typename T> T *Singleton<T>::sInstance = nullptr;
template <typename T> std::once_flag Singleton<T>::sCallFlag;

using WindowPositionCallback = void (*)(void *userPtr, int xpos, int ypos);
using WindowSizeCallback = void (*)(void *userPtr, int width, int height);
using WindowCloseCallback = void (*)(void *userPtr);
using WindowRefreshCallback = void (*)(void *userPtr);
using WindowFocusCallback = void (*)(void *userPtr, int focused);
using WindowIconifyCallback = void (*)(void *userPtr, int iconified);
using WindowMaximizeCallback = void (*)(void *userPtr, int maximized);
using WindowFramebufferSizeCallback = void (*)(void *userPtr, int width,
                                               int height);
using WindowContentScaleCallback = void (*)(void *userPtr, float xscale,
                                            float yscale);
using MousebuttonCallback = void (*)(void *userPtr, int button, int action,
                                     Modifier mods);
using CursorPositionCallback = void (*)(void *userPtr, double xpos,
                                        double ypos);
using CursorEnterCallback = void (*)(void *userPtr, int entered);
using ScrollCallback = void (*)(void *userPtr, double xoffset, double yoffset);
using KeyCallback = void (*)(void *userPtr, Key key);
using CharCallback = void (*)(void *userPtr, unsigned codepoint);
using DropCallback = void (*)(void *userPtr, Vec<Str> paths);

// Use to select opengl color frame buffer attachement.
enum class Attachment {
  COLOR0 = GL_COLOR_ATTACHMENT0,
  COLOR1 = GL_COLOR_ATTACHMENT1,
  COLOR2 = GL_COLOR_ATTACHMENT2,
  COLOR3 = GL_COLOR_ATTACHMENT3,
  COLOR4 = GL_COLOR_ATTACHMENT4,
  COLOR5 = GL_COLOR_ATTACHMENT5,
  COLOR6 = GL_COLOR_ATTACHMENT6,
  COLOR7 = GL_COLOR_ATTACHMENT7,
  COLOR8 = GL_COLOR_ATTACHMENT8,
  COLOR9 = GL_COLOR_ATTACHMENT9,
  COLOR10 = GL_COLOR_ATTACHMENT10,
  COLOR11 = GL_COLOR_ATTACHMENT11,
  COLOR12 = GL_COLOR_ATTACHMENT12,
  COLOR13 = GL_COLOR_ATTACHMENT13,
  COLOR14 = GL_COLOR_ATTACHMENT14,
  COLOR15 = GL_COLOR_ATTACHMENT15,
  COLOR16 = GL_COLOR_ATTACHMENT16,
  COLOR17 = GL_COLOR_ATTACHMENT17,
  COLOR18 = GL_COLOR_ATTACHMENT18,
  COLOR19 = GL_COLOR_ATTACHMENT19,
  COLOR20 = GL_COLOR_ATTACHMENT20,
  COLOR21 = GL_COLOR_ATTACHMENT21,
  COLOR22 = GL_COLOR_ATTACHMENT22,
  COLOR23 = GL_COLOR_ATTACHMENT23,
  COLOR24 = GL_COLOR_ATTACHMENT24,
  COLOR25 = GL_COLOR_ATTACHMENT25,
  COLOR26 = GL_COLOR_ATTACHMENT26,
  COLOR27 = GL_COLOR_ATTACHMENT27,
  COLOR28 = GL_COLOR_ATTACHMENT28,
  COLOR29 = GL_COLOR_ATTACHMENT29,
  COLOR30 = GL_COLOR_ATTACHMENT30,
  COLOR31 = GL_COLOR_ATTACHMENT31
};

// Use to select buffer to clear.
enum class BufferBit {
  DEPTH_BUFFER = GL_DEPTH_BUFFER_BIT,
  STENCIL_BUFFER = GL_STENCIL_BUFFER_BIT,
  COLOR_BUFFER = GL_COLOR_BUFFER_BIT
};

// Use to select opengl buffer usage.
enum class BufferUsage {
  STREAM_DRAW = GL_STREAM_DRAW,
  STREAM_READ = GL_STREAM_READ,
  STREAM_COPY = GL_STREAM_COPY,
  STATIC_DRAW = GL_STATIC_DRAW,
  STATIC_READ = GL_STATIC_READ,
  STATIC_COPY = GL_STATIC_COPY,
  DYNAMIC_DRAW = GL_DYNAMIC_DRAW,
  DYNAMIC_READ = GL_DYNAMIC_READ,
  DYNAMIC_COPY = GL_DYNAMIC_COPY
};

// Use to select opengl buffer type.
enum class BufferType {
  ARRAY_BUFFER = GL_ARRAY_BUFFER,
  ELEMENT_BUFFER = GL_ELEMENT_ARRAY_BUFFER
};

// Use to select opengl cube map face direction.
enum class CubeFace {
  RIGHT = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
  LEFT = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
  TOP = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
  BOTTOM = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
  FRONT = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
  BACK = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

// Use to select opengl drawing mode.
enum class DrawMode {
  POINTS = GL_POINTS,
  LINES = GL_LINES,
  LINE_LOOP = GL_LINE_LOOP,
  LINE_STRIP = GL_LINE_STRIP,
  TRIANGLES = GL_TRIANGLES,
  TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
  TRIANGLE_FAN = GL_TRIANGLE_FAN,
  QUADS = GL_QUADS
};

// Use to select opengl texture filtering type.
enum class FilterType {
  NEAREST = GL_NEAREST,
  LINEAR = GL_LINEAR,
  NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST, // MIN_FILTER only
  LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST,   // MIN_FILTER only
  NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,   // MIN_FILTER only
  LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR      // MIN_FILTER only
};

// Use to select input mode.
enum class InputType {
  CURSOR = GLFW_CURSOR,
  STICKY_KEYS = GLFW_STICKY_KEYS,
  STICKY_MOUSE_BUTTONS = GLFW_STICKY_MOUSE_BUTTONS,
  LOCK_KEY_MODS = GLFW_LOCK_KEY_MODS,
  RAW_MOUSE_MOTION = GLFW_RAW_MOUSE_MOTION
};

// Use to select keyboard key.
enum class Keyboard {
  K_SPACE = GLFW_KEY_SPACE,
  K_APOSTROPHE = GLFW_KEY_APOSTROPHE,
  K_COMMA = GLFW_KEY_COMMA,
  K_MINUS = GLFW_KEY_MINUS,
  K_PERIOD = GLFW_KEY_PERIOD,
  K_SLASH = GLFW_KEY_SLASH,
  K_0 = GLFW_KEY_0,
  K_1 = GLFW_KEY_1,
  K_2 = GLFW_KEY_2,
  K_3 = GLFW_KEY_3,
  K_4 = GLFW_KEY_4,
  K_5 = GLFW_KEY_5,
  K_6 = GLFW_KEY_6,
  K_7 = GLFW_KEY_7,
  K_8 = GLFW_KEY_8,
  K_9 = GLFW_KEY_9,
  K_SEMICOLON = GLFW_KEY_SEMICOLON,
  K_EQUAL = GLFW_KEY_EQUAL,
  K_A = GLFW_KEY_A,
  K_B = GLFW_KEY_B,
  K_C = GLFW_KEY_C,
  K_D = GLFW_KEY_D,
  K_E = GLFW_KEY_E,
  K_F = GLFW_KEY_F,
  K_G = GLFW_KEY_G,
  K_H = GLFW_KEY_H,
  K_I = GLFW_KEY_I,
  K_J = GLFW_KEY_J,
  K_K = GLFW_KEY_K,
  K_L = GLFW_KEY_L,
  K_M = GLFW_KEY_M,
  K_N = GLFW_KEY_N,
  K_O = GLFW_KEY_O,
  K_P = GLFW_KEY_P,
  K_Q = GLFW_KEY_Q,
  K_R = GLFW_KEY_R,
  K_S = GLFW_KEY_S,
  K_T = GLFW_KEY_T,
  K_U = GLFW_KEY_U,
  K_V = GLFW_KEY_V,
  K_W = GLFW_KEY_W,
  K_X = GLFW_KEY_X,
  K_Y = GLFW_KEY_Y,
  K_Z = GLFW_KEY_Z,
  K_LEFT_BRACKET = GLFW_KEY_LEFT_BRACKET,
  K_BACKSLASH = GLFW_KEY_BACKSLASH,
  K_RIGHT_BRACKET = GLFW_KEY_RIGHT_BRACKET,
  K_GRAVE_ACCENT = GLFW_KEY_GRAVE_ACCENT,
  K_WORLD_1 = GLFW_KEY_WORLD_1,
  K_WORLD_2 = GLFW_KEY_WORLD_2,
  K_ESCAPE = GLFW_KEY_ESCAPE,
  K_ENTER = GLFW_KEY_ENTER,
  K_TAB = GLFW_KEY_TAB,
  K_BACKSPACE = GLFW_KEY_BACKSPACE,
  K_INSERT = GLFW_KEY_INSERT,
  K_DELETE = GLFW_KEY_DELETE,
  K_RIGHT = GLFW_KEY_RIGHT,
  K_LEFT = GLFW_KEY_LEFT,
  K_DOWN = GLFW_KEY_DOWN,
  K_UP = GLFW_KEY_UP,
  K_PAGE_UP = GLFW_KEY_PAGE_UP,
  K_PAGE_DOWN = GLFW_KEY_PAGE_DOWN,
  K_HOME = GLFW_KEY_HOME,
  K_END = GLFW_KEY_END,
  K_CAPS_LOCK = GLFW_KEY_CAPS_LOCK,
  K_SCROLL_LOCK = GLFW_KEY_SCROLL_LOCK,
  K_NUM_LOCK = GLFW_KEY_NUM_LOCK,
  K_PRINT_SCREEN = GLFW_KEY_PRINT_SCREEN,
  K_PAUSE = GLFW_KEY_PAUSE,
  K_F1 = GLFW_KEY_F1,
  K_F2 = GLFW_KEY_F2,
  K_F3 = GLFW_KEY_F3,
  K_F4 = GLFW_KEY_F4,
  K_F5 = GLFW_KEY_F5,
  K_F6 = GLFW_KEY_F6,
  K_F7 = GLFW_KEY_F7,
  K_F8 = GLFW_KEY_F8,
  K_F9 = GLFW_KEY_F9,
  K_F10 = GLFW_KEY_F10,
  K_F11 = GLFW_KEY_F11,
  K_F12 = GLFW_KEY_F12,
  K_F13 = GLFW_KEY_F13,
  K_F14 = GLFW_KEY_F14,
  K_F15 = GLFW_KEY_F15,
  K_F16 = GLFW_KEY_F16,
  K_F17 = GLFW_KEY_F17,
  K_F18 = GLFW_KEY_F18,
  K_F19 = GLFW_KEY_F19,
  K_F20 = GLFW_KEY_F20,
  K_F21 = GLFW_KEY_F21,
  K_F22 = GLFW_KEY_F22,
  K_F23 = GLFW_KEY_F23,
  K_F24 = GLFW_KEY_F24,
  K_F25 = GLFW_KEY_F25,
  K_KP_0 = GLFW_KEY_KP_0,
  K_KP_1 = GLFW_KEY_KP_1,
  K_KP_2 = GLFW_KEY_KP_2,
  K_KP_3 = GLFW_KEY_KP_3,
  K_KP_4 = GLFW_KEY_KP_4,
  K_KP_5 = GLFW_KEY_KP_5,
  K_KP_6 = GLFW_KEY_KP_6,
  K_KP_7 = GLFW_KEY_KP_7,
  K_KP_8 = GLFW_KEY_KP_8,
  K_KP_9 = GLFW_KEY_KP_9,
  K_KP_DECIMAL = GLFW_KEY_KP_DECIMAL,
  K_KP_DIVIDE = GLFW_KEY_KP_DIVIDE,
  K_KP_MULTIPLY = GLFW_KEY_KP_MULTIPLY,
  K_KP_SUBTRACT = GLFW_KEY_KP_SUBTRACT,
  K_KP_ADD = GLFW_KEY_KP_ADD,
  K_KP_ENTER = GLFW_KEY_KP_ENTER,
  K_KP_EQUAL = GLFW_KEY_KP_EQUAL,
  K_LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
  K_LEFT_CONTROL = GLFW_KEY_LEFT_CONTROL,
  K_LEFT_ALT = GLFW_KEY_LEFT_ALT,
  K_LEFT_SUPER = GLFW_KEY_LEFT_SUPER,
  K_RIGHT_SHIFT = GLFW_KEY_RIGHT_SHIFT,
  K_RIGHT_CONTROL = GLFW_KEY_RIGHT_CONTROL,
  K_RIGHT_ALT = GLFW_KEY_RIGHT_ALT,
  K_RIGHT_SUPER = GLFW_KEY_RIGHT_SUPER,
  K_MENU = GLFW_KEY_MENU,
  K_LAST = GLFW_KEY_LAST
};

// Use to select mouse button input.
enum class MousebuttonInput {
  BUTTON1 = GLFW_MOUSE_BUTTON_1,
  LEFT_BUTTON = GLFW_MOUSE_BUTTON_LEFT,
  BUTTON2 = GLFW_MOUSE_BUTTON_2,
  RIGHT_BUTTON = GLFW_MOUSE_BUTTON_RIGHT,
  BUTTON3 = GLFW_MOUSE_BUTTON_3,
  MIDDLE_BUTTON = GLFW_MOUSE_BUTTON_MIDDLE,
  BUTTON4 = GLFW_MOUSE_BUTTON_4,
  BUTTON5 = GLFW_MOUSE_BUTTON_5,
  BUTTON6 = GLFW_MOUSE_BUTTON_6,
  BUTTON7 = GLFW_MOUSE_BUTTON_7,
  BUTTON8 = GLFW_MOUSE_BUTTON_8
};

// Use to select opengl texture target to activate.
enum class TextureTargets {
  TEX_1 = GL_TEXTURE0,
  TEX_2 = GL_TEXTURE1,
  TEX_3 = GL_TEXTURE2,
  TEX_4 = GL_TEXTURE3,
  TEX_5 = GL_TEXTURE4,
  TEX_6 = GL_TEXTURE5,
  TEX_7 = GL_TEXTURE6,
  TEX_8 = GL_TEXTURE7,
  TEX_9 = GL_TEXTURE8,
  TEX_10 = GL_TEXTURE9,
  TEX_11 = GL_TEXTURE10,
  TEX_12 = GL_TEXTURE11,
  TEX_13 = GL_TEXTURE12,
  TEX_14 = GL_TEXTURE13,
  TEX_15 = GL_TEXTURE14,
  TEX_16 = GL_TEXTURE15,
  TEX_17 = GL_TEXTURE16,
  TEX_18 = GL_TEXTURE17,
  TEX_19 = GL_TEXTURE18,
  TEX_20 = GL_TEXTURE19,
  TEX_21 = GL_TEXTURE20,
  TEX_22 = GL_TEXTURE21,
  TEX_23 = GL_TEXTURE22,
  TEX_24 = GL_TEXTURE23,
  TEX_25 = GL_TEXTURE24,
  TEX_26 = GL_TEXTURE25,
  TEX_27 = GL_TEXTURE26,
  TEX_28 = GL_TEXTURE27,
  TEX_29 = GL_TEXTURE28,
  TEX_30 = GL_TEXTURE29,
  TEX_31 = GL_TEXTURE30,
  TEX_32 = GL_TEXTURE31
};

// Use to select opengl texture wrapping type.
enum class WrappingType {
  CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
  CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
  MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
  REPEAT = GL_REPEAT
};

static unsigned COLOR_BUFFERS[] = {
    (unsigned)Attachment::COLOR0,  (unsigned)Attachment::COLOR1,
    (unsigned)Attachment::COLOR2,  (unsigned)Attachment::COLOR3,
    (unsigned)Attachment::COLOR4,  (unsigned)Attachment::COLOR5,
    (unsigned)Attachment::COLOR6,  (unsigned)Attachment::COLOR7,
    (unsigned)Attachment::COLOR8,  (unsigned)Attachment::COLOR9,
    (unsigned)Attachment::COLOR10, (unsigned)Attachment::COLOR11,
    (unsigned)Attachment::COLOR12, (unsigned)Attachment::COLOR13,
    (unsigned)Attachment::COLOR14, (unsigned)Attachment::COLOR15,
    (unsigned)Attachment::COLOR16, (unsigned)Attachment::COLOR17,
    (unsigned)Attachment::COLOR18, (unsigned)Attachment::COLOR19,
    (unsigned)Attachment::COLOR20, (unsigned)Attachment::COLOR21,
    (unsigned)Attachment::COLOR22, (unsigned)Attachment::COLOR23,
    (unsigned)Attachment::COLOR24, (unsigned)Attachment::COLOR25,
    (unsigned)Attachment::COLOR26, (unsigned)Attachment::COLOR27,
    (unsigned)Attachment::COLOR28, (unsigned)Attachment::COLOR29,
    (unsigned)Attachment::COLOR30, (unsigned)Attachment::COLOR31};
} // namespace GeoFrame

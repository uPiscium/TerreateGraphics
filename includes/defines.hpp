#ifndef __TERREATE_GRAPHICS_DEFINES_HPP__
#define __TERREATE_GRAPHICS_DEFINES_HPP__

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <deque>
#include <fstream>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include <TerreateLogger/TerreateLogger.hpp>
#include <TerreateMath/TerreateMath.hpp>

// Defines
#define TC_DISABLE_COPY_AND_ASSIGN(Type)                                       \
  Type(Type const &) = delete;                                                 \
  Type &operator=(Type const &) = delete

// Constants
#define GLAD_H <glad/gl.h>
#define GLFW_H <GLFW/glfw3.h>
#define TC_PI 3.14159265358979

#ifndef TC_UNICODE_HALF_SPACE
#define TC_UNICODE_HALF_SPACE 32
#endif // TC_UNICODE_HALF_SPACE

#ifndef TC_UNICODE_FULL_SPACE
#define TC_UNICODE_FULL_SPACE 32306
#endif // TC_UNICODE_FULL_SPACE

#include GLAD_H
#include GLFW_H

namespace TerreateGraphics::Defines {
// Core variables
extern bool GLFW_INITIALIZED;
extern bool GLAD_INITIALIZED;

// Type aliases
// TC types (TerreateCore types)
typedef bool TCbool;
typedef int8_t TCi8;
typedef uint8_t TCu8;
typedef int16_t TCi16;
typedef uint16_t TCu16;
typedef int32_t TCi32;
typedef uint32_t TCu32;
typedef int64_t TCi64;
typedef uint64_t TCu64;
typedef float TCfloat;
typedef double TCdouble;

// TL types (TerreateLogger types)
typedef TerreateLogger::Interface::ILogger ILogger;
typedef TerreateLogger::Loggers::ConsoleLogger ConsoleLogger;
typedef TerreateLogger::Loggers::FileLogger FileLogger;
typedef TerreateLogger::Manager::LoggerManager LoggerManager;

// TM types (TerreateMath types)
typedef TerreateMath::Math::complex complex;
typedef TerreateMath::Math::fraction fraction;
typedef TerreateMath::Math::matrix matrix;

typedef TerreateMath::Math::vec2 vec2;
typedef TerreateMath::Math::vec3 vec3;
typedef TerreateMath::Math::vec4 vec4;

typedef TerreateMath::Math::mat2 mat2;
typedef TerreateMath::Math::mat2x3 mat2x3;
typedef TerreateMath::Math::mat2x4 mat2x4;
typedef TerreateMath::Math::mat3x2 mat3x2;
typedef TerreateMath::Math::mat3 mat3;
typedef TerreateMath::Math::mat3x4 mat3x4;
typedef TerreateMath::Math::mat4x2 mat4x2;
typedef TerreateMath::Math::mat4x3 mat4x3;
typedef TerreateMath::Math::mat4 mat4;

typedef TerreateMath::Math::quat quat;

// Standard types
typedef TCbool Bool;
typedef TCi8 Byte;
typedef TCu8 Ubyte;
typedef TCi16 Short;
typedef TCu16 Ushort;
typedef TCi32 Int;
typedef TCu32 Uint;
typedef TCi64 Long;
typedef TCu64 Ulong;
typedef TCfloat Float;
typedef TCdouble Double;

typedef std::mutex Mutex;
typedef std::condition_variable CondVar;
typedef std::thread Thread;
typedef TCu32 ID;
typedef TCu64 Index;
typedef TCu64 EventID;
typedef TCu64 Size;
typedef std::string Str;
typedef std::wstring WStr;
typedef std::stringstream Stream;
typedef std::ifstream InputFileStream;
typedef std::ofstream OutputFileStream;

template <typename S, typename T> using Map = std::unordered_map<S, T>;
template <typename T> using Pair = std::pair<T, T>;
template <typename T> using Set = std::unordered_set<T>;
template <typename T> using Shared = std::shared_ptr<T>;
template <typename T, typename Container = std::deque<T>>
using Queue = std::queue<T, Container>;
template <typename T> using UniqueLock = std::unique_lock<T>;
template <typename T> using LockGuard = std::lock_guard<T>;
template <typename T> using Atomic = std::atomic<T>;
template <typename T> using Vec = std::vector<T>;
template <typename T> using Function = std::function<T>;

// Chrono types
namespace chrono = std::chrono;
typedef chrono::nanoseconds NanoSec;
typedef chrono::system_clock SystemClock;
typedef chrono::steady_clock SteadyClock;
template <typename T> using ZonedTimeT = chrono::zoned_time<T>;
using ZonedTime = ZonedTimeT<NanoSec>;

// Callbacks
using ErrorCallback = std::function<void(int errorCode, char const *message)>;
using MonitorCallback = std::function<void(GLFWmonitor *monitor, int event)>;
using JoystickCallback = std::function<void(int joystickID, int event)>;

// Concepts
template <typename Derived, typename Base>
concept extends = std::derived_from<Derived, Base>;
template <typename Enum>
concept enumtype = std::is_enum_v<Enum>;

// Functions
template <typename T> inline Str ToStr(T const &val) {
  Stream stream;
  stream << val;
  return stream.str();
}
template <typename S, typename T> inline S DurationCast(T const &time) {
  return chrono::duration_cast<S>(time);
}
inline SteadyClock::duration SinceEpoch() {
  return SteadyClock::now().time_since_epoch();
}
inline Double GetNanoSec() {
  return static_cast<Double>(DurationCast<NanoSec>(SinceEpoch()).count()) /
         1000000000;
}
inline ZonedTime GetCurrentTime() {
  return ZonedTime{chrono::current_zone(), SystemClock::now()};
}

// Structs
struct Modifier {
public:
  TCbool shift = false;
  TCbool control = false;
  TCbool alt = false;
  TCbool super = false;
  TCbool capsLock = false;
  TCbool numLock = false;

public:
  Modifier(int mods_)
      : shift(mods_ & GLFW_MOD_SHIFT), control(mods_ & GLFW_MOD_CONTROL),
        alt(mods_ & GLFW_MOD_ALT), super(mods_ & GLFW_MOD_SUPER),
        capsLock(mods_ & GLFW_MOD_CAPS_LOCK),
        numLock(mods_ & GLFW_MOD_NUM_LOCK) {}
};

struct Key {
public:
  TCi32 key = 0;
  TCi32 scancode = 0;
  TCi32 action = 0;
  Modifier mods = 0;

public:
  Key(int key_, int scancode_, int action_, int mods_)
      : key(key_), scancode(scancode_), action(action_), mods(mods_) {}
};

// Enums
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

// Use to select blending function.
enum class BlendingFuntion {
  ZERO = GL_ZERO,
  ONE = GL_ONE,
  SRC_COLOR = GL_SRC_COLOR,
  ONE_MINUS_SRC_COLOR = GL_ONE_MINUS_SRC_COLOR,
  DST_COLOR = GL_DST_COLOR,
  ONE_MINUS_DST_COLOR = GL_ONE_MINUS_DST_COLOR,
  SRC_ALPHA = GL_SRC_ALPHA,
  ONE_MINUS_SRC_ALPHA = GL_ONE_MINUS_SRC_ALPHA,
  DST_ALPHA = GL_DST_ALPHA,
  ONE_MINUS_DST_ALPHA = GL_ONE_MINUS_DST_ALPHA,
  CONSTANT_COLOR = GL_CONSTANT_COLOR,
  ONE_MINUS_CONSTANT_COLOR = GL_ONE_MINUS_CONSTANT_COLOR,
  CONSTANT_ALPHA = GL_CONSTANT_ALPHA,
  ONE_MINUS_CONSTANT_ALPHA = GL_ONE_MINUS_CONSTANT_ALPHA,
  SRC_ALPHA_SATURATE = GL_SRC_ALPHA_SATURATE
};

// Use to select material color property.
enum class ColorProperty { AMBIENT, DIFFUSE, SPECULAR, EMISSIVE };

// Use to select opengl cube map face direction.
enum class CubeFace {
  RIGHT = GL_TEXTURE_CUBE_MAP_POSITIVE_X,
  LEFT = GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
  TOP = GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
  BOTTOM = GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
  FRONT = GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
  BACK = GL_TEXTURE_CUBE_MAP_NEGATIVE_Z
};

// Use to select opengl culling face.
enum class CullingFace {
  FRONT = GL_FRONT,
  BACK = GL_BACK,
  FRONT_AND_BACK = GL_FRONT_AND_BACK
};

// Use to select opengl culling mode.
enum class CullingMode { CW = GL_CW, CCW = GL_CCW };

// Use to select opengl cursor mode.
enum class CursorMode {
  NORMAL = GLFW_CURSOR_NORMAL,
  HIDDEN = GLFW_CURSOR_HIDDEN,
  DISABLED = GLFW_CURSOR_DISABLED
};

// Use to select opengl standard cursor shape.
enum class CursorShape {
  ARROW = GLFW_ARROW_CURSOR,
  IBEAM = GLFW_IBEAM_CURSOR,
  CROSSHAIR = GLFW_CROSSHAIR_CURSOR,
  HAND = GLFW_HAND_CURSOR,
  HRESIZE = GLFW_HRESIZE_CURSOR,
  VRESIZE = GLFW_VRESIZE_CURSOR
};

// Use to select opengl depth function.
enum class DepthFunction {
  NEVER = GL_NEVER,
  LESS = GL_LESS,
  EQUAL = GL_EQUAL,
  LEQUAL = GL_LEQUAL,
  GREATER = GL_GREATER,
  NOTEQUAL = GL_NOTEQUAL,
  GEQUAL = GL_GEQUAL,
  ALWAYS = GL_ALWAYS
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

// Use to select material float property.
enum class FloatProperty {
  SHININESS,
  TRANSPARENCY,
  REFLECTIVITY,
  REFRACTIVITY
};

// Use to select opengl feature.
enum class GLFeature {
  BLEND = GL_BLEND,
  CULL_FACE = GL_CULL_FACE,
  DEPTH_TEST = GL_DEPTH_TEST,
  DITHER = GL_DITHER,
  POLYGON_OFFSET_FILL = GL_POLYGON_OFFSET_FILL,
  SAMPLE_ALPHA_TO_COVERAGE = GL_SAMPLE_ALPHA_TO_COVERAGE,
  SAMPLE_COVERAGE = GL_SAMPLE_COVERAGE,
  SCISSOR_TEST = GL_SCISSOR_TEST,
  STENCIL_TEST = GL_STENCIL_TEST
};

// Use to select input mode.
enum class InputType {
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

// Use to select data type included in buffer.
enum class ModelFlag : TCu8 {
  EMPTY = 0,
  POSITION = 1,
  NORMAL = 1 << 1,
  UV = 1 << 2,
  COLOR = 1 << 3,
  JOINT = 1 << 4,
  WEIGHT = 1 << 5,
  MATERIAL = 1 << 6,
  MORPH = 1 << 7
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

// Use to select opengl stencil function.
enum class StencilFunction {
  NEVER = GL_NEVER,
  LESS = GL_LESS,
  EQUAL = GL_EQUAL,
  LEQUAL = GL_LEQUAL,
  GREATER = GL_GREATER,
  NOTEQUAL = GL_NOTEQUAL,
  GEQUAL = GL_GEQUAL,
  ALWAYS = GL_ALWAYS
};

// Use to select opengl stencil operation.
enum class StencilOperation {
  KEEP = GL_KEEP,
  ZERO = GL_ZERO,
  REPLACE = GL_REPLACE,
  INCR = GL_INCR,
  INCR_WRAP = GL_INCR_WRAP,
  DECR = GL_DECR,
  DECR_WRAP = GL_DECR_WRAP,
  INVERT = GL_INVERT
};

// Use to select material texture property.
enum class TextureProperty {
  NORMAL,
  AMBIENT,
  DIFFUSE,
  SPECULAR,
  EMISSIVE,
  DISSOLVE,
  SHININESS,
  REFLECTION,
  REFRACTION
};

// Use to select opengl texture target to activate.
enum class TextureTargets {
  TEX_0 = GL_TEXTURE0,
  TEX_1 = GL_TEXTURE1,
  TEX_2 = GL_TEXTURE2,
  TEX_3 = GL_TEXTURE3,
  TEX_4 = GL_TEXTURE4,
  TEX_5 = GL_TEXTURE5,
  TEX_6 = GL_TEXTURE6,
  TEX_7 = GL_TEXTURE7,
  TEX_8 = GL_TEXTURE8,
  TEX_9 = GL_TEXTURE9,
  TEX_10 = GL_TEXTURE10,
  TEX_11 = GL_TEXTURE11,
  TEX_12 = GL_TEXTURE12,
  TEX_13 = GL_TEXTURE13,
  TEX_14 = GL_TEXTURE14,
  TEX_15 = GL_TEXTURE15,
  TEX_16 = GL_TEXTURE16,
  TEX_17 = GL_TEXTURE17,
  TEX_18 = GL_TEXTURE18,
  TEX_19 = GL_TEXTURE19,
  TEX_20 = GL_TEXTURE20,
  TEX_21 = GL_TEXTURE21,
  TEX_22 = GL_TEXTURE22,
  TEX_23 = GL_TEXTURE23,
  TEX_24 = GL_TEXTURE24,
  TEX_25 = GL_TEXTURE25,
  TEX_26 = GL_TEXTURE26,
  TEX_27 = GL_TEXTURE27,
  TEX_28 = GL_TEXTURE28,
  TEX_29 = GL_TEXTURE29,
  TEX_30 = GL_TEXTURE30,
  TEX_31 = GL_TEXTURE31,
};

// Use to select opengl texture wrapping type.
enum class WrappingType {
  CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
  CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
  MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
  REPEAT = GL_REPEAT
};

static unsigned COLOR_BUFFERS[] = {
    (GLenum)Attachment::COLOR0,  (GLenum)Attachment::COLOR1,
    (GLenum)Attachment::COLOR2,  (GLenum)Attachment::COLOR3,
    (GLenum)Attachment::COLOR4,  (GLenum)Attachment::COLOR5,
    (GLenum)Attachment::COLOR6,  (GLenum)Attachment::COLOR7,
    (GLenum)Attachment::COLOR8,  (GLenum)Attachment::COLOR9,
    (GLenum)Attachment::COLOR10, (GLenum)Attachment::COLOR11,
    (GLenum)Attachment::COLOR12, (GLenum)Attachment::COLOR13,
    (GLenum)Attachment::COLOR14, (GLenum)Attachment::COLOR15,
    (GLenum)Attachment::COLOR16, (GLenum)Attachment::COLOR17,
    (GLenum)Attachment::COLOR18, (GLenum)Attachment::COLOR19,
    (GLenum)Attachment::COLOR20, (GLenum)Attachment::COLOR21,
    (GLenum)Attachment::COLOR22, (GLenum)Attachment::COLOR23,
    (GLenum)Attachment::COLOR24, (GLenum)Attachment::COLOR25,
    (GLenum)Attachment::COLOR26, (GLenum)Attachment::COLOR27,
    (GLenum)Attachment::COLOR28, (GLenum)Attachment::COLOR29,
    (GLenum)Attachment::COLOR30, (GLenum)Attachment::COLOR31};
} // namespace TerreateGraphics::Defines

#endif // __TERREATE_GRAPHICS_DEFINES_HPP__

#include <audiotest.hpp>
#include <coretest.hpp>
#include <exceptions.hpp>

namespace Core = Terreate::Test::Core;
namespace Audio = Terreate::Test::Audio;

int main() {
#ifdef BUILD_CORE_TESTS // This is defined in the CMakeLists.txt / Default: OFF
  // Core tests
  Core::TestEvent();
  Core::TestExecutor();
  Core::TestNullable();
  Core::TestObject();
  Core::TestProperty();
  Core::TestUUID();
#endif // BUILD_CORE_TESTS

#ifdef BUILD_AUDIO_TESTS // This is defined in the CMakeLists.txt / Default: OFF
  // Audio tests
  Audio::TestAudio();
#endif // BUILD_AUDIO_TESTS
}

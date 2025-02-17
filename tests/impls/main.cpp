#include <coretest.hpp>
#include <exceptions.hpp>

namespace Core = Terreate::Test::Core;

int main() {
  // Core tests
  Core::TestEvent();
  Core::TestExecutor();
  Core::TestNullable();
  Core::TestUUID();
}

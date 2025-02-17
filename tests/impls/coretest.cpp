#include <coretest.hpp>

namespace Terreate::Test::Core {

// Event
void TestEvent() {
  std::cout << ">>>>>>>>>>>>>>>>>>>> TestEvent\n";
  Event<int, int> event;
  event += [](int a, int b) { std::cout << a + b << std::endl; };
  event += [](int a, int b) { std::cout << a * b << std::endl; };
  event.Publish(1, 2);
  event.Publish(3, 4);
  // event -= [](int a, int b) { std::cout << a + b << std::endl; };
  event.Publish(5, 6);
}

// Executor
void Task(int n, int i) {
  for (int j = 0; j < n; ++j) {
    std::this_thread::sleep_for(std::chrono::milliseconds(i * 300));
    std::cout << "Task " << i << std::endl;
  }
}

void ErrorTask() {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  throw Exceptions::ExecutorError("This is expected error.");
}

struct Callable {
  void operator()() { std::cout << "Callable" << std::endl; }
};

void TestExecutor() {
  std::cout << ">>>>>>>>>>>>>>>>>>>> TestExecutor\n";
  Executor executor;
  for (int i = 0; i < 3; ++i) {
    executor.Schedule([i]() { Task(3, i); });
  }
  executor.Schedule(ErrorTask);
  executor.Schedule(Callable());

  executor.WaitForAll();

  for (auto &e : executor.GetExceptions()) {
    std::cout << e.what() << std::endl;
  }
}

// Nullable
void TestNullable() {
  std::cout << ">>>>>>>>>>>>>>>>>>>> TestNullable\n";
  Nullable<int> a = 1;
  Nullable<int> b = 2;
  Nullable<int> c = a + b;
  std::cout << c.Value() << std::endl;

  Nullable<int> d;
  std::cout << d.Valid() << std::endl;

  try {
    std::cout << d.Value() << std::endl;
  } catch (Exceptions::NullReferenceException &e) {
    std::cout << e.what() << std::endl;
  }
}

// UUID
void TestUUID() {
  std::cout << ">>>>>>>>>>>>>>>>>>>> TestUUID\n";
  UUID uuid;
  std::cout << uuid.ToString() << std::endl;
}

} // namespace Terreate::Test::Core

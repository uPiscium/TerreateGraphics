#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "interface.hpp"
#include "object.hpp"
#include <thread>

namespace GeoFrame {
class JobBase : public Geobject {
private:
  friend class JobSystem;

private:
  bool mFinished;
  Vec<JobBase *> mDependencies;
  std::exception_ptr mException = nullptr;

private:
  void Run();

public:
  JobBase() {}
  JobBase(JobBase *dependency) { mDependencies.push_back(dependency); }
  JobBase(Vec<JobBase *> const &dependencies) : mDependencies(dependencies) {}

  bool IsExecutable() const;
  bool IsFinished() const { return mFinished; }
  virtual void Execute() = 0;
};

class SimpleJob : public JobBase {
private:
  Function<void()> mFunction;

public:
  SimpleJob() {}
  SimpleJob(Function<void()> const &target) : mFunction(target) {}

  void Execute() { mFunction(); }

  SimpleJob &operator=(Function<void()> const &target);
};

class JobSystem : public Geobject {
private:
  Queue<JobBase *> mJobs;
  Vec<Thread> mWorkers;
  Vec<Thread> mDaemons;
  Mutex mJobLock;
  CondVar mCondition;
  Atomic<bool> mComplete = false;
  Atomic<bool> mStop = false;
  Atomic<unsigned> mNumJobs = 0;

private:
  void WorkerThread();
  void DaemonThread(JobBase *job);

public:
  JobSystem(unsigned const &numThreads = std::thread::hardware_concurrency());
  ~JobSystem() override { this->Stop(); }

  void Stop();
  void Schedule(JobBase *job);
  void Daemonize(JobBase *job) {
    mDaemons.emplace_back(Thread([this, job] { this->DaemonThread(job); }));
  }
  void WaitForAll() { mComplete.wait(false); }
};

} // namespace GeoFrame

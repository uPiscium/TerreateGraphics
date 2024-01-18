#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include <thread>

namespace GeoFrame {
class IJob : public Geobject {
private:
  friend class JobSystem;

private:
  bool mFinished;
  Vec<IJob *> mDependencies;
  std::exception_ptr mException = nullptr;

private:
  void Run();

public:
  IJob() {}
  IJob(IJob *dependency) { mDependencies.push_back(dependency); }
  IJob(Vec<IJob *> const &dependencies) : mDependencies(dependencies) {}

  bool IsExecutable() const;
  bool IsFinished() const { return mFinished; }
  virtual void Execute() = 0;

  operator bool() const override { return this->IsFinished(); }
};

class SimpleJob : public IJob {
private:
  Function<void()> mFunction;

public:
  SimpleJob() {}
  SimpleJob(Function<void()> const &target) : mFunction(target) {}
  SimpleJob(Function<void()> const &target, IJob *const dependency)
      : mFunction(target), IJob(dependency) {}
  SimpleJob(Function<void()> const &target, Vec<IJob *> const &dependencies)
      : mFunction(target), IJob(dependencies) {}

  void Execute() override { mFunction(); }

  SimpleJob &operator=(Function<void()> const &target);
  operator bool() const override { return this->IsFinished(); }
};

class JobSystem : public Geobject {
private:
  Queue<IJob *> mJobs;
  Vec<Thread> mWorkers;
  Vec<Thread> mDaemons;
  Mutex mJobLock;
  CondVar mCondition;
  Atomic<bool> mComplete = false;
  Atomic<bool> mStop = false;
  Atomic<unsigned> mNumJobs = 0;

private:
  void WorkerThread();
  void DaemonThread(IJob *job);

public:
  JobSystem(unsigned const &numThreads = std::thread::hardware_concurrency());
  ~JobSystem() override { this->Stop(); }

  void Stop();
  void Schedule(IJob *job);
  void Daemonize(IJob *job) {
    mDaemons.emplace_back(Thread([this, job] { this->DaemonThread(job); }));
  }
  void WaitForAll() { mComplete.wait(false); }

  operator bool() const override { return mComplete; }
};

} // namespace GeoFrame

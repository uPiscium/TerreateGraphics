#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "interface.hpp"
#include "object.hpp"

namespace GeoFrame {
class JobBase : public IRunnable {
private:
  bool mComplete = false;

public:
  virtual ~JobBase() override {}

  bool IsComplete() const { return mComplete; }

  virtual void Run() override {}

  void operator()();
};

class JobHandle : public Geobject {
private:
  SharedFuture<void> mHandle;

public:
  JobHandle(SharedFuture<void> const handle) : mHandle(handle) {}
  JobHandle(JobHandle const &other) : mHandle(other.mHandle) {}
  JobHandle(JobHandle &&other) : mHandle(std::move(other.mHandle)) {}
  ~JobHandle() override { this->Delete(); }

  bool IsValid() const { return mHandle.valid(); }

  void Delete() override { mHandle.get(); }
  void Wait() const { mHandle.wait(); }

  JobHandle &operator=(JobHandle const &other);
};

class JobSystem : public Geobject {
private:
  Vec<Thread> mThreads;
  Vec<Thread> mDaemonThreads;
  Queue<PackagedTask<void()>> mJobs;
  CondVar mCondition;
  Mutex mQueueMutex;

  Atomic<bool> mRunning = true;
  Atomic<bool> mStop = false;
  Atomic<int> mNumJobs = 0;

private:
  void WorkerThread();
  void DaemonThread(JobBase *job);

public:
  JobSystem(unsigned const &numThreads = std::thread::hardware_concurrency());
  ~JobSystem() override { this->Delete(); }

  void Delete() override;
  JobHandle Schedule(JobBase *job);
  JobHandle Schedule(JobBase *job, JobHandle const dependency);
  JobHandle Schedule(JobBase *job, Vec<JobHandle> const dependencies);
  void Daemonize(JobBase *job) {
    mDaemonThreads.push_back(
        Thread([this, job]() { this->DaemonThread(job); }));
  }
  void WaitForAll() { mRunning.wait(false); }
  void Stop();
};
} // namespace GeoFrame

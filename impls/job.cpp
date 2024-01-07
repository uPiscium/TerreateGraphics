#include "../includes/job.hpp"

namespace GeoFrame {
void JobBase::operator()() {
  this->Run();
  mComplete = true;
}

JobHandle &JobHandle::operator=(JobHandle const &other) {
  if (this != &other) {
    mHandle = other.mHandle;
  }

  return *this;
}

void JobSystem::WorkerThread() {
  while (!mStop) {
    PackagedTask<void()> job;

    { // Critical section to get job from queue
      UniqueLock<Mutex> lock(mQueueMutex);
      mCondition.wait(lock, [this]() { return !mJobs.empty() || !mStop; });

      job = std::move(mJobs.front());
      mJobs.pop();
    }

    if (mJobs.empty()) {
      break;
    }

    job();

    if (mNumJobs-- == 1) {
      mRunning = false;
      mCondition.notify_all();
    }
  }
}

void JobSystem::DaemonThread(JobBase *job) {
  while (!mStop) {
    (*job)();
  }
}

JobSystem::JobSystem(unsigned const &numThreads) {
  mNumJobs = 0;
  mRunning = false;
  mStop = false;

  for (unsigned i = 0; i < numThreads; i++) {
    mThreads.push_back(Thread([this]() { this->WorkerThread(); }));
  }
}

void JobSystem::Delete() {
  if (mRunning) {
    Stop();
  }
}

JobHandle JobSystem::Schedule(JobBase *job) {
  PackagedTask<void()> task([job]() { (*job)(); });
  JobHandle handle(task.get_future());

  { // Critical section to add job to queue
    LockGuard<Mutex> lock(mQueueMutex);
    mJobs.push(std::move(task));
  }

  mNumJobs++;
  mRunning = true;
  mCondition.notify_one();
}

JobHandle JobSystem::Schedule(JobBase *job, JobHandle const dependency) {
  auto wrapper = [job, dependency]() {
    dependency.Wait();
    (*job)();
  };
  PackagedTask<void()> task(wrapper);
  JobHandle handle(task.get_future());

  { // Critical section to add job to queue
    LockGuard<Mutex> lock(mQueueMutex);
    mJobs.push(std::move(task));
  }

  mNumJobs++;
  mRunning = true;
  mCondition.notify_one();

  return handle;
}

JobHandle JobSystem::Schedule(JobBase *job, Vec<JobHandle> const dependencies) {
  auto wrapper = [job, dependencies]() {
    for (auto &dependency : dependencies) {
      if (dependency.IsValid()) {
        dependency.Wait();
      }
    }
    (*job)();
  };
  PackagedTask<void()> task(wrapper);
  JobHandle handle(task.get_future());

  { // Critical section to add job to queue
    LockGuard<Mutex> lock(mQueueMutex);
    mJobs.push(std::move(task));
  }

  mNumJobs++;
  mRunning = true;
  mCondition.notify_one();

  return handle;
}

void JobSystem::Stop() {
  mStop = true;
  mCondition.notify_all();

  for (auto &thread : mThreads) {
    if (thread.joinable()) {
      thread.join();
    }
  }
}
} // namespace GeoFrame

#include "../includes/job.hpp"

namespace TerreateCore::Job {
using namespace TerreateCore::Defines;

void JobBase::Run() {
  try {
    this->Execute();
  } catch (...) {
    mException = std::current_exception();
  }
  mFinished = true;
}

JobBase::JobBase() : mFinished(false) {
  TC_TRACE_CALL(LOCATION(JobBase));
  TC_DEBUG_CALL("JobBase generated.");
}

JobBase::JobBase(JobBase *dependency) : mFinished(false) {
  TC_TRACE_CALL(LOCATION(JobBase));
  TC_DEBUG_CALL("JobBase generated with dependency.");
  mDependencies.push_back(const_cast<JobBase *>(dependency));
}

JobBase::JobBase(std::vector<JobBase *> const &dependencies)
    : mDependencies(dependencies), mFinished(false) {
  TC_TRACE_CALL(LOCATION(JobBase));
  TC_DEBUG_CALL("JobBase generated with dependencies.");
}

JobBase::~JobBase() {
  TC_TRACE_CALL(LOCATION(JobBase));
  TC_DEBUG_CALL("JobBase deleted.");
}

bool JobBase::IsExecutable() const {
  TC_TRACE_CALL(LOCATION(JobBase));

  for (auto &dep : mDependencies) {
    if (!dep->IsFinished()) {
      return false;
    }
  }
  return true;
}

bool JobBase::IsFinished() const {
  TC_TRACE_CALL(LOCATION(JobBase));

  return mFinished;
}

SimpleJob::SimpleJob(Function<void()> const &target) : mFunction(target) {
  TC_TRACE_CALL(LOCATION(SimpleJob));
  TC_DEBUG_CALL("SimpleJob generated.");
}

SimpleJob::SimpleJob(Function<void()> const &target, JobBase *dependency)
    : JobBase(dependency), mFunction(target) {
  TC_TRACE_CALL(LOCATION(SimpleJob));
  TC_DEBUG_CALL("SimpleJob generated with dependency.");
}

SimpleJob::SimpleJob(Function<void()> const &target,
                     std::vector<JobBase *> const &dependencies)
    : JobBase(dependencies), mFunction(target) {
  TC_TRACE_CALL(LOCATION(SimpleJob));
  TC_DEBUG_CALL("SimpleJob generated with dependencies.");
}

SimpleJob::~SimpleJob() {
  TC_TRACE_CALL(LOCATION(SimpleJob));
  TC_DEBUG_CALL("SimpleJob deleted.");
}

SimpleJob &SimpleJob::operator=(Function<void()> const &target) {
  TC_TRACE_CALL(LOCATION(SimpleJob));

  mFunction = target;
  return *this;
}

void SimpleJob::Execute() {
  TC_TRACE_CALL(LOCATION(SimpleJob));

  mFunction();
}

void JobSystem::WorkerThread() {
  TC_TRACE_CALL(LOCATION(JobSystem));

  while (!mStop) {
    JobBase *job = nullptr;
    {
      UniqueLock<Mutex> lock(mJobLock);
      mCondition.wait(lock, [this] { return !mJobs.empty() || mStop; });

      if (mJobs.empty()) {
        return;
      }

      while (true) {
        job = std::move(mJobs.front());
        mJobs.pop();

        if (job->IsExecutable()) {
          break;
        } else {
          mJobs.push(job);
        }
      }
    }

    job->Run();

    if (mNumJobs.fetch_sub(1) == 1) {
      mComplete.store(true);
      mComplete.notify_all();
    }
  }
}

void JobSystem::DaemonThread(JobBase *job) {
  TC_TRACE_CALL(LOCATION(JobSystem));

  while (!mStop) {
    job->Run();
  }
}

JobSystem::JobSystem(Uint const &numThreads) {
  TC_TRACE_CALL(LOCATION(JobSystem));

  for (Uint i = 0; i < numThreads; ++i) {
    mWorkers.emplace_back(Thread([this] { this->WorkerThread(); }));
  }
  TC_DEBUG_CALL("JobSystem generated.");
}

JobSystem::~JobSystem() {
  TC_TRACE_CALL(LOCATION(JobSystem));

  this->Stop();
  TC_DEBUG_CALL("JobSystem deleted.");
}

void JobSystem::Stop() {
  TC_TRACE_CALL(LOCATION(JobBase));

  mStop.store(true);
  mCondition.notify_all();

  for (auto &worker : mWorkers) {
    worker.join();
  }

  for (auto &daemon : mDaemons) {
    daemon.join();
  }
}

void JobSystem::Schedule(JobBase *job) {
  TC_TRACE_CALL(LOCATION(JobSystem));

  {
    UniqueLock<Mutex> lock(mJobLock);
    mJobs.push(job);
    mNumJobs.fetch_add(1);
    mComplete.store(false);
  }

  mCondition.notify_one();
}

void JobSystem::Daemonize(JobBase *job) {
  TC_TRACE_CALL(LOCATION(JobSystem));

  mDaemons.emplace_back(Thread([this, job] { this->DaemonThread(job); }));
}

void JobSystem::WaitForAll() {
  TC_TRACE_CALL(LOCATION(JobSystem));

  UniqueLock<Mutex> lock(mJobLock);
  mComplete.wait(false);
}
} // namespace TerreateCore::Job

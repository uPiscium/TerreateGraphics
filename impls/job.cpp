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
  Logger::Trace(LOCATION(JobBase));
  Logger::Debug("JobBase generated.");
}

JobBase::JobBase(JobBase *dependency) : mFinished(false) {
  Logger::Trace(LOCATION(JobBase));
  Logger::Debug("JobBase generated with dependency.");
  mDependencies.push_back(const_cast<JobBase *>(dependency));
}

JobBase::JobBase(std::vector<JobBase *> const &dependencies)
    : mDependencies(dependencies), mFinished(false) {
  Logger::Trace(LOCATION(JobBase));
  Logger::Debug("JobBase generated with dependencies.");
}

JobBase::~JobBase() {
  Logger::Trace(LOCATION(JobBase));
  Logger::Debug("JobBase deleted.");
}

bool JobBase::IsExecutable() const {
  Logger::Trace(LOCATION(JobBase));

  for (auto &dep : mDependencies) {
    if (!dep->IsFinished()) {
      return false;
    }
  }
  return true;
}

bool JobBase::IsFinished() const {
  Logger::Trace(LOCATION(JobBase));

  return mFinished;
}

SimpleJob::SimpleJob(Function<void()> const &target) : mFunction(target) {
  Logger::Trace(LOCATION(SimpleJob));
  Logger::Debug("SimpleJob generated.");
}

SimpleJob::SimpleJob(Function<void()> const &target, JobBase *dependency)
    : JobBase(dependency), mFunction(target) {
  Logger::Trace(LOCATION(SimpleJob));
  Logger::Debug("SimpleJob generated with dependency.");
}

SimpleJob::SimpleJob(Function<void()> const &target,
                     std::vector<JobBase *> const &dependencies)
    : JobBase(dependencies), mFunction(target) {
  Logger::Trace(LOCATION(SimpleJob));
  Logger::Debug("SimpleJob generated with dependencies.");
}

SimpleJob::~SimpleJob() {
  Logger::Trace(LOCATION(SimpleJob));
  Logger::Debug("SimpleJob deleted.");
}

SimpleJob &SimpleJob::operator=(Function<void()> const &target) {
  Logger::Trace(LOCATION(SimpleJob));

  mFunction = target;
  return *this;
}

void SimpleJob::Execute() {
  Logger::Trace(LOCATION(SimpleJob));

  mFunction();
}

void JobSystem::WorkerThread() {
  Logger::Trace(LOCATION(JobSystem));

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
  Logger::Trace(LOCATION(JobSystem));

  while (!mStop) {
    job->Run();
  }
}

JobSystem::JobSystem(Uint const &numThreads) {
  Logger::Trace(LOCATION(JobSystem));

  for (Uint i = 0; i < numThreads; ++i) {
    mWorkers.emplace_back(Thread([this] { this->WorkerThread(); }));
  }
  Logger::Debug("JobSystem generated.");
}

JobSystem::~JobSystem() {
  Logger::Trace(LOCATION(JobSystem));

  this->Stop();
  Logger::Debug("JobSystem deleted.");
}

void JobSystem::Stop() {
  Logger::Trace(LOCATION(JobBase));

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
  Logger::Trace(LOCATION(JobSystem));

  {
    UniqueLock<Mutex> lock(mJobLock);
    mJobs.push(job);
    mNumJobs.fetch_add(1);
    mComplete.store(false);
  }

  mCondition.notify_one();
}

void JobSystem::Daemonize(JobBase *job) {
  Logger::Trace(LOCATION(JobSystem));

  mDaemons.emplace_back(Thread([this, job] { this->DaemonThread(job); }));
}

void JobSystem::WaitForAll() {
  Logger::Trace(LOCATION(JobSystem));

  UniqueLock<Mutex> lock(mJobLock);
  mComplete.wait(false);
}
} // namespace TerreateCore::Job

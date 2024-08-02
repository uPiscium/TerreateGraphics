#ifndef __TERREATE_GRAPHICS_JOB_HPP__
#define __TERREATE_GRAPHICS_JOB_HPP__

#include "defines.hpp"

namespace TerreateGraphics::Job {
using namespace TerreateGraphics::Defines;

class JobBase : public TerreateObjectBase {
private:
  friend class JobSystem;

private:
  Bool mFinished;
  Vec<JobBase *> mDependencies;
  std::exception_ptr mException = nullptr;

private:
  void Run();

public:
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   */
  JobBase() : mFinished(false) {}
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   */
  JobBase(JobBase *dependency) : mFinished(false) {
    mDependencies.push_back(dependency);
  }
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   */
  JobBase(Vec<JobBase *> const &dependencies)
      : mDependencies(dependencies), mFinished(false) {}
  virtual ~JobBase() override {}

  /*
   * @brief: Returns true if the job is ready to be executed.
   * @return: True if the job is ready to be executed.
   */
  Bool IsExecutable() const;
  /*
   * @brief: Returns true if the job has finished executing.
   * @return: True if the job has finished executing.
   */
  Bool IsFinished() const { return mFinished; }
  /*
   * @brief: Overload this function to execute the job.
   */
  virtual void Execute() = 0;

  virtual operator Bool() const override { return this->IsFinished(); }
};

class SimpleJob : public JobBase {
private:
  Function<void()> mFunction;

public:
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   */
  SimpleJob() : mFunction(nullptr) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   */
  SimpleJob(Function<void()> const &target) : mFunction(target) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   */
  SimpleJob(Function<void()> const &target, JobBase *const dependency)
      : JobBase(dependency), mFunction(target) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   */
  SimpleJob(Function<void()> const &target, Vec<JobBase *> const &dependencies)
      : JobBase(dependencies), mFunction(target) {}
  virtual ~SimpleJob() override {}

  /*
   * @brief: Executes the target function.
   */
  virtual void Execute() override { mFunction(); }

  SimpleJob &operator=(Function<void()> const &target);
  virtual operator Bool() const override { return this->IsFinished(); }
};

class JobSystem : public TerreateObjectBase {
private:
  Queue<JobBase *> mJobs;
  Vec<Thread> mWorkers;
  Vec<Thread> mDaemons;
  Mutex mJobLock;
  CondVar mCondition;
  Atomic<Bool> mComplete = false;
  Atomic<Bool> mStop = false;
  Atomic<Uint> mNumJobs = 0;

private:
  void WorkerThread();
  void DaemonThread(JobBase *job);

public:
  /*
   * @brief: JobSystem is a thread pool that can be used to execute jobs
   * asynchronously.
   * @param: numThreads: The number of threads to be used by the JobSystem.
   */
  JobSystem(Uint const &numThreads = std::thread::hardware_concurrency());
  virtual ~JobSystem() override { this->Stop(); }

  /*
   * @brief: Stop the JobSystem and stop all job executions.
   */
  virtual void Stop();
  /*
   * @brief: Schedule a job to be executed.
   * @param: job: The job to be executed.
   */
  virtual void Schedule(JobBase *job);
  /*
   * @brief: Set a job to be a daemon. A daemon is a job that is executed
   * asynchronously and does not block the JobSystem from stopping.
   * @param: job: The job to be executed.
   */
  virtual void Daemonize(JobBase *job) {
    mDaemons.emplace_back(Thread([this, job] { this->DaemonThread(job); }));
  }
  /*
   * @brief: Wait for all jobs to finish executing.
   */
  virtual void WaitForAll();

  virtual operator Bool() const override { return mComplete; }
};
} // namespace TerreateGraphics::Job

#endif // __TERREATE_GRAPHICS_JOB_HPP__

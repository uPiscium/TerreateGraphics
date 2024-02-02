#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include <thread>

namespace GeoFrame {
namespace Utils {
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
  /*
   * @brief: IJob is an interface for a job that can be executed by the
   * JobSystem.
   */
  IJob() {}
  /*
   * @brief: IJob is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   */
  IJob(IJob *dependency) { mDependencies.push_back(dependency); }
  /*
   * @brief: IJob is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   */
  IJob(Vec<IJob *> const &dependencies) : mDependencies(dependencies) {}

  /*
   * @brief: Returns true if the job is ready to be executed.
   * @return: True if the job is ready to be executed.
   */
  bool IsExecutable() const;
  /*
   * @brief: Returns true if the job has finished executing.
   * @return: True if the job has finished executing.
   */
  bool IsFinished() const { return mFinished; }
  /*
   * @brief: Overload this function to execute the job.
   */
  virtual void Execute() = 0;

  operator bool() const override { return this->IsFinished(); }
};

class SimpleJob : public IJob {
private:
  Function<void()> mFunction;

public:
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   */
  SimpleJob() {}
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
  SimpleJob(Function<void()> const &target, IJob *const dependency)
      : mFunction(target), IJob(dependency) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   */
  SimpleJob(Function<void()> const &target, Vec<IJob *> const &dependencies)
      : mFunction(target), IJob(dependencies) {}

  /*
   * @brief: Executes the target function.
   */
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
  /*
   * @brief: JobSystem is a thread pool that can be used to execute jobs
   * asynchronously.
   * @param: numThreads: The number of threads to be used by the JobSystem.
   */
  JobSystem(unsigned const &numThreads = std::thread::hardware_concurrency());
  ~JobSystem() override { this->Stop(); }

  /*
   * @brief: Stop the JobSystem and stop all job executions.
   */
  void Stop();
  /*
   * @brief: Schedule a job to be executed.
   * @param: job: The job to be executed.
   */
  void Schedule(IJob *job);
  /*
   * @brief: Set a job to be a daemon. A daemon is a job that is executed
   * asynchronously and does not block the JobSystem from stopping.
   * @param: job: The job to be executed.
   */
  void Daemonize(IJob *job) {
    mDaemons.emplace_back(Thread([this, job] { this->DaemonThread(job); }));
  }
  /*
   * @brief: Wait for all jobs to finish executing.
   */
  void WaitForAll() { mComplete.wait(false); }

  operator bool() const override { return mComplete; }
};
} // namespace Utils
} // namespace GeoFrame

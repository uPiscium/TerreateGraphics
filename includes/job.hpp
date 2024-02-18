#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "object.hpp"
#include <thread>

namespace GeoFrame {
namespace Utils {
class JobBase : public Geobject {
private:
  friend class JobSystem;

private:
  Bool mFinished;
  Vec<JobBase *> mDependencies;
  std::exception_ptr mException = nullptr;

private:
  void Run();

public:
  static ObjectID const sOID;

public:
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   */
  JobBase() : Geobject(JobBase::sOID) {}
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   */
  JobBase(JobBase *dependency) : Geobject(JobBase::sOID) {
    mDependencies.push_back(dependency);
  }
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   */
  JobBase(Vec<JobBase *> const &dependencies)
      : Geobject(JobBase::sOID), mDependencies(dependencies) {}
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  JobBase(ObjectID const &id) : Geobject(id) {}
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  JobBase(JobBase *dependency, ObjectID const &id) : Geobject(id) {
    mDependencies.push_back(dependency);
  }
  /*
   * @brief: JobBase is an interface for a job that can be executed by the
   * JobSystem.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  JobBase(Vec<JobBase *> const &dependencies, ObjectID const &id)
      : Geobject(id), mDependencies(dependencies) {}
  virtual ~JobBase() override = default;

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
  static ObjectID const sOID;

public:
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   */
  SimpleJob() : JobBase(SimpleJob::sOID) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   */
  SimpleJob(Function<void()> const &target)
      : JobBase(SimpleJob::sOID), mFunction(target) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   */
  SimpleJob(Function<void()> const &target, JobBase *const dependency)
      : mFunction(target), JobBase(dependency, SimpleJob::sOID) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   */
  SimpleJob(Function<void()> const &target, Vec<JobBase *> const &dependencies)
      : mFunction(target), JobBase(dependencies, JobBase::sOID) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  SimpleJob(Function<void()> const &target, ObjectID const &id)
      : JobBase(id), mFunction(target) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependency: The job that must be finished before this job can be
   * executed.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  SimpleJob(Function<void()> const &target, JobBase *const dependency,
            ObjectID const &id)
      : JobBase(dependency, id), mFunction(target) {}
  /*
   * @brief: SimpleJob is a wrapper for a function that can be executed by the
   * JobSystem. It can be used to execute a function asynchronously, or to
   * execute a function after a dependency has finished.
   * @param: target: The function to be executed.
   * @param: dependencies: The jobs that must be finished before this job can be
   * executed.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  SimpleJob(Function<void()> const &target, Vec<JobBase *> const &dependencies,
            ObjectID const &id)
      : JobBase(dependencies, id), mFunction(target) {}
  virtual ~SimpleJob() override = default;

  /*
   * @brief: Executes the target function.
   */
  virtual void Execute() override { mFunction(); }

  SimpleJob &operator=(Function<void()> const &target);
  virtual operator Bool() const override { return this->IsFinished(); }
};

class JobSystem : public Geobject {
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
  static ObjectID const sOID;

public:
  /*
   * @brief: JobSystem is a thread pool that can be used to execute jobs
   * asynchronously.
   * @param: numThreads: The number of threads to be used by the JobSystem.
   */
  JobSystem(Uint const &numThreads = std::thread::hardware_concurrency());
  /*
   * @brief: JobSystem is a thread pool that can be used to execute jobs
   * asynchronously.
   * @param: numThreads: The number of threads to be used by the JobSystem.
   * @param: id: the id of the object
   * @note: This constructor is used in derived classes to set the id
   * of the object.
   */
  JobSystem(Uint const &numThreads, ObjectID const &id);
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
  virtual void WaitForAll() { mComplete.wait(false); }

  virtual operator Bool() const override { return mComplete; }
};
} // namespace Utils
} // namespace GeoFrame

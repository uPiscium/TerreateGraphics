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

  virtual void Preprocess() {}
  virtual void Postprocess() {}
  virtual void Run() override {}

  void operator()();
};

class Worker : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(Worker);

private:
  Shared<Queue<Shared<JobBase>>> mJobQueue;
  Shared<CondVar> mCondVar;
  Shared<Mutex> mQueueMutex;
  Thread mThread;

public:
  Worker(Shared<Queue<Shared<JobBase>>> jobQueue, Shared<CondVar> condVar,
         Shared<Mutex> queueMutex)
      : mJobQueue(jobQueue), mCondVar(condVar),
        mThread([this]() { this->WorkerThread(); }) {}
  ~Worker() override { this->Delete(); }

  void Delete() override;
  void WorkerThread();
};

class JobSystem : public Geobject {
private:
  Queue<Shared<JobBase>> mJobQueue;
  CondVar mCondVar;
  Mutex mQueueMutex;
  Vec<Worker> mWorkers;

public:
  JobSystem(unsigned const &numWorkers);
  ~JobSystem() override { this->Delete(); }

  void Delete() override;
  void Schedule(JobBase *job);
  void Wait();
};
} // namespace GeoFrame

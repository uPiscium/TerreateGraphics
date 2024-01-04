#pragma once
#include "defines.hpp"
#include "exceptions.hpp"
#include "interface.hpp"
#include "object.hpp"

namespace GeoFrame {
class Job : public IRunnable {
public:
  Job() {}
  virtual ~Job() override {}

  virtual void Preprocess() {}
  virtual void Postprocess() {}
  virtual void operator()() override {}
};

class Worker : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(Worker);
};

class JobHandler : public Geobject {
private:
  M_DISABLE_COPY_AND_ASSIGN(JobHandler);

private:
  Queue<Shared<Job>> mJobQueue;
  Mutex mPopMutex;
  Vec<Thread> mThreads;
  CondVar mCondition;

public:
  JobHandler();
  explicit JobHandler(size_t const &numFreeThreads = 32);
  ~JobHandler() override { this->Delete(); }

  void Delete() override;
};
} // namespace GeoFrame

#include "../includes/job.hpp"

namespace GeoFrame {
void JobBase::operator()() {
  this->Preprocess();
  this->Run();
  this->Postprocess();
  mComplete = true;
}

void Worker::WorkerThread() {
  while (true) {
    Shared<JobBase> job = nullptr;
    {
      UniqueLock<Mutex> lock(*mQueueMutex);
      mCondVar->wait(lock, [this]() { return !mJobQueue->empty(); });

      job = std::move(mJobQueue->front());
      mJobQueue->pop();
    }
    (*job)();
  }
}

void JobSystem::Schedule(JobBase *job) {
  {
    UniqueLock<Mutex> lock(mQueueMutex);
    mJobQueue.push(Shared<JobBase>(job));
  }
  mCondVar.notify_one();
}
} // namespace GeoFrame

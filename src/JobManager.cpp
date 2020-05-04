#include "JobManager.h"
#include <random>

/**
 * Multithreading approach adapted from https://stackoverflow.com/a/21396485
 */
JobManager::JobManager(int NumCores, int NumJobs,
                       std::function<void(int)> JobFunction)
    : num_cores_(NumCores), num_jobs_(NumJobs) {
  auto Worker = [&]() {
    while (true) {
      int NextJobIndex = job_queue_.workerStart();
      if (NextJobIndex == -1)
        return;
      jobs_[NextJobIndex].run();
      job_queue_.workerDone();
    }
  };
  jobs_.resize(NumJobs, Job(JobFunction));
  workers_.resize(NumCores);
  for (int I = 0; I < NumCores; I++) {
    workers_[I] = std::thread(Worker);
  }
}
void JobManager::shuffleJobsInButterflyOrder(int Min, int Max) {
  if (Min > Max)
    return;
  jobs_[Min].setIndex(Max);
  if (Min == Max)
    return;
  jobs_[Max].setIndex(Min);
  int Mid = (Min + Max) / 2;
  shuffleJobsInButterflyOrder(Min + 1, Mid);
  shuffleJobsInButterflyOrder(Mid + 1, Max - 1);
}
void JobManager::compute() {
  shuffleJobsInButterflyOrder(0, num_jobs_ - 1);
  job_queue_.masterStart(num_jobs_);
  job_queue_.masterDone();
}
JobManager::~JobManager() {
  job_queue_.masterKill();
  for (std::thread &Worker : workers_)
    Worker.join();
}

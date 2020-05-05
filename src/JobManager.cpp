#include "JobManager.h"

/**
 * Multithreading approach from https://stackoverflow.com/a/21396485
 */
JobManager::JobManager(int NumCores, int NumJobs, std::shared_ptr<Image> Image,
                       std::shared_ptr<Fractal> Fractal)
    : num_cores_(NumCores), num_jobs_(NumJobs), image_(Image),
      fractal_(Fractal) {
  auto Worker = [&]() {
    while (true) {
      int NextJobIndex = job_queue_.workerStart();
      if (NextJobIndex == -1)
        return;
      jobs_[NextJobIndex].run();
      job_queue_.workerDone();
    }
  };
  jobs_.resize(NumJobs, FractalRow(fractal_));
  for (int I = 0; I < NumJobs; I++) {
    jobs_[I].setup(Image, I);
  }
  workers_.resize(NumCores);
  for (int I = 0; I < NumCores; I++) {
    workers_[I] = std::thread(Worker);
  }
}
void JobManager::compute() {
  job_queue_.masterStart(num_jobs_);
  job_queue_.masterDone();
}
JobManager::~JobManager() {
  job_queue_.masterKill();
  for (std::thread &Worker : workers_)
    Worker.join();
}

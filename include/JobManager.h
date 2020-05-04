#ifndef FRACTALCREATOR_INCLUDE_JOBMANAGER_H
#define FRACTALCREATOR_INCLUDE_JOBMANAGER_H

#include "Job.h"
#include "JobQueue.h"
#include "utils.h"
#include <memory>
#include <thread>
#include <vector>

class JobManager {
public:
  JobManager(int NumCores, int NumJobs, std::function<void(int)> JobFunction);
  void compute();
  ~JobManager();
  JobManager(const JobManager &) = delete;
  JobManager &operator=(const JobManager &) = delete;

private:
  int num_cores_;
  int num_jobs_;
  std::vector<std::thread> workers_;
  std::vector<Job> jobs_;
  JobQueue job_queue_;
  void shuffleJobsInButterflyOrder(int Min, int Max);
};

#endif // FRACTALCREATOR_INCLUDE_JOBMANAGER_H

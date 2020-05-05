#ifndef FRACTALCREATOR_INCLUDE_JOBMANAGER_H
#define FRACTALCREATOR_INCLUDE_JOBMANAGER_H

#include "FractalRow.h"
#include "JobQueue.h"
#include "utils.h"
#include <memory>
#include <thread>
#include <vector>

class JobManager {
public:
  JobManager(int NumCores, int NumJobs, std::shared_ptr<Image> Image,
             std::shared_ptr<Fractal> Fractal);
  void compute();
  ~JobManager();

private:
  int num_cores_;
  int num_jobs_;
  std::shared_ptr<Image> image_;
  std::shared_ptr<Fractal> fractal_;
  std::vector<std::thread> workers_;
  std::vector<FractalRow> jobs_;
  JobQueue job_queue_;
};

#endif // FRACTALCREATOR_INCLUDE_JOBMANAGER_H

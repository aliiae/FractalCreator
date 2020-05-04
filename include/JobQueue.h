#ifndef FRACTALCREATOR_INCLUDE_JOBQUEUE_H
#define FRACTALCREATOR_INCLUDE_JOBQUEUE_H
#include <condition_variable>
#include <stdatomic.h>

/**
 * Adapted from https://stackoverflow.com/a/21396485
 */
class JobQueue {
  friend class JobManager;

private:
  std::mutex queue_lock;
  std::condition_variable work;
  std::condition_variable done;
  int number_of_pending_jobs;
  atomic_int number_of_active_jobs;
  bool should_kill_workers;

  JobQueue();
  int workerStart();
  void workerDone();
  void masterStart(int NumJobs);
  void masterDone();
  void masterKill();
};

#endif // FRACTALCREATOR_INCLUDE_JOBQUEUE_H

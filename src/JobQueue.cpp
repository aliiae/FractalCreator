#include <JobQueue.h>

JobQueue::JobQueue() : number_of_pending_jobs{0}, should_kill_workers{false} {}
/**
 * Return the index of the job to process (if a worker needs to be killed,
 * return -1).
 */
int JobQueue::workerStart() {
  std::unique_lock<std::mutex> Waiter(queue_lock);
  while (!number_of_pending_jobs && !should_kill_workers) {
    work.wait(Waiter);
  }
  return should_kill_workers ? -1 : --number_of_pending_jobs;
}
/**
 * Notify the master as soon as there are no more active jobs.
 */
void JobQueue::workerDone() {
  if (!--number_of_active_jobs) {
    done.notify_one();
  }
}
/**
 * Notify workers to start jobs.
 */
void JobQueue::masterStart(int NumJobs) {
  std::unique_lock<std::mutex> Waiter(queue_lock);
  number_of_pending_jobs = number_of_active_jobs = NumJobs;
  work.notify_all();
}
/**
 * Wait for workers to finish.
 */
void JobQueue::masterDone() {
  std::unique_lock<std::mutex> Waiter(queue_lock);
  while (number_of_active_jobs) {
    done.wait(Waiter);
  }
}
/**
 * Notify all workers and terminate them.
 */
void JobQueue::masterKill() {
  should_kill_workers = true;
  work.notify_all();
}

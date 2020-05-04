#ifndef FRACTALCREATOR_INCLUDE_JOB_H
#define FRACTALCREATOR_INCLUDE_JOB_H
#include <functional>

class Job {
public:
  Job(std::function<void(int)> &Function);
  void run();
  void setIndex(int Index);

private:
  std::function<void(int)> &function_;
  int index_;
};

#endif // FRACTALCREATOR_INCLUDE_JOB_H

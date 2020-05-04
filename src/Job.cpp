#include "Job.h"

Job::Job(std::function<void(int)> &Function) : function_(Function) {}
void Job::run() { function_(index_); }
void Job::setIndex(int Index) { index_ = Index; }

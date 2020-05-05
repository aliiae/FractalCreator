#include "Creator.h"
#include <Image.h>
#include <JobManager.h>
#include <iostream>
#include <memory>

using Clock = std::chrono::system_clock;
using Seconds = std::chrono::duration<double>;

void Creator::draw() {
  std::cout << "Generating a " << fractal_->getName() << " fractal of order "
            << fractal_->getOrder() << " with max " << max_iterations_
            << " iterations";
  std::cout.flush();
  auto Start = Clock::now();
  std::shared_ptr<Image> ResultImage = std::make_shared<Image>(width_, height_);
  JobManager Manager = JobManager(4, height_, ResultImage, fractal_);
  Manager.compute();
  Seconds ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)" << std::endl;
  std::cout << "Saving to " << image_path_;
  std::cout.flush();
  Start = Clock::now();
  ResultImage->save(image_path_);
  ElapsedSeconds = Clock::now() - Start;
  std::cout << " (" << ElapsedSeconds.count() << " seconds)" << std::endl;
}
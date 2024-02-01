#include "../includes/jobTest.hpp"

using namespace GeoFrame::Utils;

void Job1() {
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "Job1" << std::endl;
}

void Job2() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Job2" << std::endl;
}

void Job3() {
  std::this_thread::sleep_for(std::chrono::seconds(1));
  std::cout << "Job3" << std::endl;
}

void job_test() {
  JobSystem jobs;
  SimpleJob job1(Job1);
  SimpleJob job2(Job2, &job1);
  SimpleJob job3(Job3);

  jobs.Schedule(&job1);
  jobs.Schedule(&job2);
  jobs.Schedule(&job3);
  jobs.Schedule(&job3);
  jobs.Schedule(&job3);
  jobs.Schedule(&job3);

  jobs.WaitForAll();
}

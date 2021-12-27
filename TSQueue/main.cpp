#include <iostream>
#include <thread>

#include "TSQueue.hpp"

void thread1(TSQueue<int> &q) {
  int sleep_time = 100;
  std::this_thread::sleep_for(std::chrono::milliseconds(sleep_time));
  q.push(sleep_time);
  q.push(sleep_time + 1);
  q.push(sleep_time + 2);
  std::cout << "thread1 exit." << std::endl;
}

void thread2(TSQueue<int> &q) {
  std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  int sleep_time;
  q.wait_and_pop(sleep_time);
  std::cout << "sleep_time: " << sleep_time << std::endl;
  q.wait_and_pop(sleep_time);
  std::cout << "sleep_time2: " << sleep_time << std::endl;
  q.wait_and_pop(sleep_time);
  std::cout << "sleep_time3: " << sleep_time << std::endl;
  std::cout << "thread2 exit." << std::endl;
}

int main() {
  TSQueue<int> tsq;

  std::thread t1(thread1, std::ref(tsq));
  std::thread t2(thread2, std::ref(tsq));

  t1.join();
  t2.join();

  std::cout << "main thread exit." << std::endl;

  return 0;
}

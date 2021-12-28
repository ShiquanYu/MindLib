#pragma once

#include <chrono>
#include <condition_variable>
#include <memory>
#include <mutex>
#include <queue>

template <typename T>
class TSQueue {
 public:
  TSQueue(size_t size) : max_size(size) {
  }
  virtual ~TSQueue() = default;
  TSQueue(TSQueue const &other) {
    std::lock_guard<std::mutex> lk(other.mut);
    data_queue = other.data_queue;
  }
  TSQueue &operator=(const TSQueue &) = delete;
  TSQueue(TSQueue &&) = delete;

  int push(T new_value, const int wait_ms = -1) {
    std::unique_lock<std::mutex> lk(mut);
    if (wait_ms >= 0) {
      if (!data_full_cond.wait_for(
              lk, std::chrono::milliseconds(wait_ms),
              [this] { return data_queue.size() < max_size; })) {
        /* Wait time out */
        return -1;
      }
    } else {
      data_full_cond.wait(lk, [this] { return data_queue.size() < max_size; });
    }
    data_queue.push(std::move(new_value));
    data_cond.notify_one();

    return 0;
  }

  // void push(const T &new_value, const int wait_ms = -1) {
  //   std::lock_guard<std::mutex> lk(mut);
  //   data_queue.push(new_value);
  //   data_cond.notify_one();
  // }

  // void push(T &&new_value) {
  //   std::lock_guard<std::mutex> lk(mut);
  //   data_queue.push(std::move(new_value));
  //   data_cond.notify_one();
  // }

  int wait_and_pop(T &value, const int wait_ms = -1) {
    std::unique_lock<std::mutex> lk(mut);
    if (wait_ms >= 0) {
      if (!data_cond.wait_for(lk, std::chrono::milliseconds(wait_ms),
                              [this] { return !data_queue.empty(); })) {
        /* Wait time out */
        return -1;
      }
    } else {
      data_cond.wait(lk, [this] { return !data_queue.empty(); });
    }
    value = std::move(data_queue.front());
    data_queue.pop();
    data_full_cond.notify_one();
    return 0;
  }

  bool empty() const {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.empty();
  }

  size_t size() const {
    std::lock_guard<std::mutex> lk(mut);
    return data_queue.size();
  }

 private:
  mutable std::mutex mut;
  std::queue<T> data_queue;
  std::condition_variable data_cond;
  std::condition_variable data_full_cond;
  size_t max_size;
};

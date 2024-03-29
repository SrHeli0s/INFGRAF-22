#pragma once

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

template <typename T>
class ConcurrentQueue {
    public:
    std::queue<T> getQueue() {
        return queue_;
    }

    T pop() {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty()) {
            cond_.wait(mlock);
        }
        auto val = queue_.front();
        queue_.pop();
        mlock.unlock();
        cond_.notify_one();
        return val;
    }

    void pop(T& item) {
        std::unique_lock<std::mutex> mlock(mutex_);
        while (queue_.empty()) {
            cond_.wait(mlock);
        }
        item = queue_.front();
        queue_.pop();
        mlock.unlock();
        cond_.notify_one();
    }

    void push(const T& item) {
        std::unique_lock<std::mutex> mlock(mutex_);
        queue_.push(item);
        mlock.unlock();
        cond_.notify_one();
    }

    ConcurrentQueue()=default;
    ConcurrentQueue(const ConcurrentQueue&) = delete;            // disable copying
    ConcurrentQueue& operator=(const ConcurrentQueue&) = delete; // disable assignment

    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
};
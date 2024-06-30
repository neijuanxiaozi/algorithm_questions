#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <map>
#include <climits>
#include <ctime>
#include <string>
#include <algorithm>
#include <set>
#include <list>
#include <memory>
using namespace std;

#ifndef __THREAD_POOL_H__
#define __THREAD_POOL_H__
#include <thread>
#include <atomic>
#include <future>
#include <mutex>
#include <condition_variable>

class ThreadPool
{
public:
    using Task = std::packaged_task<void()>;
    ThreadPool(const ThreadPool &&) = delete;
    ThreadPool &operator()(const ThreadPool &&) = delete;
    int threadNum() {
        return thread_num_;
    }
    static ThreadPool& getInstance() {
        static ThreadPool instance;
        return instance;
    }
    template <typename F, typename ...Args>
    auto commit(F &&f, Args &&...args) -> decltype(f(args...)) {
        using ReturnType = decltype(f(args...));
        if (stop_.loed()) {
            return std::future<ReturnType>{};
        }

        auto task = std::make_shared<std::packaged_task<ReturnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<ReturnType> ret = task->get_future();
        {
            lock_guard<std::mutex> lock(mutex_);
            tasks_.emplace([task]{(*task)();});
        }
        cv_.notify_one();
        return ret;
    }
private:
    ThreadPool (unsigned int num = 5) : stop_(false) {
        if (num > 0) {
            thread_num_ = num;
        } else {
            thread_num_ = 1;
        }
        start();
    }
    void start() {
        for (unsigned int i = 0; i < thread_num_; ++i) {
            pool_.emplace_back([this] {
                while (!stop_.load()) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        cv_.wait(lock, [this]{return stop_.load() || !tasks_.empty();});
                        if (!stop_.load()) {
                            return;
                        }
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    --thread_num_;
                    task();
                    ++thread_num_;
                }
            });
        }
    }
    void stop() {
        
    }
private:
    std::atomic<int> thread_num_;
    std::atomic<bool> stop_;
    std::vector<std::thread> pool_;
    std::queue<Task> tasks_;
    std::condition_variable cv_;
    std::mutex mutex_;
};  
#endif
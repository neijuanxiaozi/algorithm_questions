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
#include <atomic>
#include <mutex>
#include <thread>
#include <memory>
#include <queue>
#include <future>
#include <vector>
class ThreadPool
{
public:
    using Task = std::packaged_task<void()>;
    template <typename F, typename... Args>
    auto commit(F &&f, Args &&...args) -> decltype(f(args...))
    {
        using ReturnType = decltype(f(args...));
        if (stop_.load())
        {
            return std::future<ReturnType>{};
        }
        auto task = std::make_shared<std::packaged<ReturnType()>>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<ReturnType> ret = task->get_future();
        {
            std::lock_guard<std::mutex> lock(mutex_);
            tasks_.emplace([task]
                           { (*task)(); });
        }
        cv_.notify_one();
        return ret;
    }

private:
    ThreadPool(unsigned int num = 5) : stop_(false)
    {
        if (num <= 0)
        {
            thread_num_ = 1;
        }
        else
        {
            thread_num_ = num;
        }
        start();
    }
    void start()
    {
        for (unsigned int i = 0; i < thread_num_; ++i)
        {
            pool_.emplace_back([this]
                               {
                while (!stop_.load()) {
                    Task task;
                    {
                        std::unique_lock<std::mutex> lock(mutex_);
                        cv_.wait(lock, [this] {return stop_.load() || !tasks_.empty();});
                        task = std::move(tasks_.front());
                        tasks_.pop();
                    }
                    --thread_num_;
                    task();
                    ++thread_num_;
                } });
        }
    }

private:
    std::atomic<int> thread_num_;
    std::atomic<bool> stop_;
    std::vector<std::thread> pool_;
    std::queue<Task> tasks_;
    std::mutex mutex_;
    std::condition_variable cv_;
};
#endif
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
#include <condition
class ThreadPool
{
public:
    using Task = std::packaged_task<void()>;

private:

private:
    std::atomic<int> thread_num_;
    std::atomic<bool> stop_;
    std::vector<std::thread> pool_;
    std::queue<Task> tasks_;
    std::condition_variable cv_;
    std::mutex mutex_;
};  
#endif
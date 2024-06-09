#include <mutex>
#include <thread>
#include <condition_variable>
#include <queue>
#include <iostream>
#include <functional>
#include <Windows.h>
using namespace std;

typedef function<void()> Task;
int max_task_count;         // 队列最大容量
int pro_count;              // 需要生产的资源数
int producer_count;         // 生产者已经生产数量
int consumer_count;         // 消费者消费数量
queue<Task> resouce;        // 任务队列
mutex m_mtx;                // 用来保护任务队列
mutex m_pro_mtx;            // 保护生产线程任务
mutex m_con_mtx;            // 保护消费线程任务
condition_variable pro_con; // 实现生产线程同步
condition_variable con_con; // 实现消费线程同步

void init(int max_task_num, int pro_num)
{
    max_task_count = max_task_num;
    pro_count = pro_num;
    producer_count = 0;
    consumer_count = 0;
}

void func(int i)
{
    cout << "task finish" << "-----" << i << endl;
}
// 添加任务
void push(Task &task)
{
    // 生产者给队列中添加任务
    unique_lock<mutex> lck(m_mtx);

    while (resouce.size() == max_task_count)
    {
        cout << "队列已经满了，生产者等待" << endl;
        pro_con.wait(lck);
    }
    resouce.push(task);
    // 唤醒消费者线程
    con_con.notify_all();
}
// 删除任务
Task pop()
{
    // 消费者从队列中取出任务
    unique_lock<mutex> lck(m_mtx);
    while (resouce.size() == 0)
    {
        cout << "队列为空，消费者等待" << endl;
        con_con.wait(lck);
    }
    Task task = resouce.front();
    resouce.pop();
    // 唤醒生产者线程
    pro_con.notify_all();
    return task;
}
// 生产者
void proTask()
{
    while (1)
    {
        unique_lock<mutex> lck(m_pro_mtx);
        if (producer_count < pro_count)
        {
            producer_count++;
            Task task = bind(func, producer_count);
            push(task);
            cout << "生产者生成任务" << endl;
        }
        lck.unlock();
    }
}
// 消费者
void conTask()
{
    while (1)
    {
        unique_lock<mutex> lck(m_con_mtx);
        if (consumer_count < pro_count)
        {
            consumer_count++;
            Task task = pop();
            cout << "消费者消费执行任务" << endl;
            task();
        }
        lck.unlock();
    }
}

int main()
{
    init(10, 20);

    thread pro1(proTask);
    thread pro2(proTask);
    thread pro3(proTask);

    thread con1(conTask);
    thread con2(conTask);
    thread con3(conTask);

    pro1.join();
    pro2.join();
    pro3.join();

    con1.join();
    con2.join();
    con3.join();

    return 0;
}

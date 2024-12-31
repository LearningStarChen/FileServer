#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <string>
#include <cstring>
#include <condition_variable>
#include <functional>
#include <memory>
#include <sstream>
#include "log.h"

class ThreadPool {
public:
    ThreadPool(){}
    // 构造函数：创建线程
    ThreadPool(int nums);

    // 禁止拷贝构造和拷贝赋值
    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;
    // 停止线程池并等待所有线程完成
    ~ThreadPool();

    // 添加任务到线程池， 注意模板的定义和实现不能分开写
    template <class F, class... Args>
    void push(F&& f, Args&&... args) {
    {
        
        std::unique_lock<std::mutex> lock(queueMutex);
        // 封装任务为 std::function
        auto task = std::bind(std::forward<F>(f), std::forward<Args>(args)...);
        // 加入任务队列
        if (stop) {
            LOG_WARNING << "ThreadPool has been stopped, cannot push tasks";
            return;
        }

        tasks.emplace(std::move(task));
    }
    // 通知一个线程去执行任务
    condition.notify_one();
}

private:
    std::vector<std::thread> workers;              // 工作线程
    std::queue<std::function<void()>> tasks;       // 任务队列
    std::mutex queueMutex;                         // 队列锁
    std::condition_variable condition;            // 条件变量
    bool stop;                                     // 停止标志

};

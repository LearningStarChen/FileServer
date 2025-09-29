#include "../include/threadpool.h"

ThreadPool::ThreadPool(int nums) : stop(false) {
    //workers.resize(nums);
    for (size_t i = 0; i < nums; ++i) {
        workers.emplace_back([this]() {
            std::ostringstream ss;
            ss << "thread start, Tid :" << std::this_thread::get_id();
            LOG_TRACK << ss.str();
            while (true) {
                //记录从任务队列中取出的任务
                std::function<void()> task;

                // 等待并取任务
                {
                    std::unique_lock<std::mutex> lock(queueMutex);
                    condition.wait(lock, [this] {
                        return stop || !tasks.empty();
                    });
                    //取得任务前判断一下,只有当线程停止而且任务队列是空的才停止退出
                    if (stop && tasks.empty()) {
                        std::ostringstream ss;
                        ss << "thread exit, Tid :" << std::this_thread::get_id();
                        LOG_WARNING << ss.str();
                        return; // 停止线程
                    }

                    // 从任务队列中取任务
                    task = std::move(tasks.front());
                    tasks.pop();
                }
                // 执行任务
                task();
            }
        });
    }
    LOG_TRACK << "threadpool at constructor function create thread successful, waiting for task";
}

ThreadPool::~ThreadPool() {
    {
        //这样写，在线程中执行完task后会卡在wait函数，然后通知所有线程，就会判断到stop为
        // 假的，那么线程退出
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;//stop为true，也会跳过wait继续执行
    }

    // 通知所有线程继续运行，然后
    condition.notify_all();

    // 等待所有线程完成，回收线程资源
    for (std::thread& worker : workers) {
        worker.join();
    }
}





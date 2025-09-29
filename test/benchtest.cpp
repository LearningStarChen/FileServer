#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <cstring>
#include <errno.h>

const std::string APP_NAME = "./client";

struct ProcessTimeInfo {
    pid_t pid;
    int child_index;
    std::chrono::steady_clock::time_point start_time;
    std::chrono::steady_clock::time_point end_time;
    double duration_ms;
    bool completed;
};

int main() {
    const int NUM_PROCESSES = 5;
    std::vector<pid_t> child_pids;
    std::vector<ProcessTimeInfo> time_info;

    std::cout << "Starting " << NUM_PROCESSES << " processes..." << std::endl;

    auto program_start_time = std::chrono::steady_clock::now();

    // 创建子进程
    for (int i = 0; i < NUM_PROCESSES; ++i) {
        auto child_start_time = std::chrono::steady_clock::now();
        pid_t pid = fork();

        if (pid < 0) {
            std::cerr << "Fork failed for child " << i << std::endl;
            continue;
        } 
        else if (pid == 0) {
            // 子进程
            const char* argv[] = {APP_NAME.c_str(), NULL};
            execvp(argv[0], const_cast<char* const*>(argv));
            std::cerr << "Exec failed for child " << i << std::endl;
            _exit(EXIT_FAILURE); 
        } 
        else {
            // 父进程
            child_pids.push_back(pid);
            ProcessTimeInfo info;
            info.pid = pid;
            info.child_index = i;
            info.start_time = child_start_time;
            info.completed = false;
            time_info.push_back(info);
        }
    }

    // 等待所有子进程完成
    for (size_t i = 0; i < child_pids.size(); ++i) {
        int status;
        pid_t p = child_pids[i];
        waitpid(p, &status, 0);
        
        auto end_time = std::chrono::steady_clock::now();
        for (auto& info : time_info) {
            if (info.pid == p) {
                info.end_time = end_time;
                info.duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                    info.end_time - info.start_time).count();
                info.completed = true;
                break;
            }
        }
        
        std::cout << "Process " << i << " finished in " << time_info[i].duration_ms << " ms" << std::endl;
    }

    auto program_end_time = std::chrono::steady_clock::now();
    double total_duration_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        program_end_time - program_start_time).count();

    // 简化的统计报告
    std::cout << "\n=== Summary ===" << std::endl;
    
    double total_children_time = 0.0;
    int completed_count = 0;
    
    for (const auto& info : time_info) {
        if (info.completed) {
            total_children_time += info.duration_ms;
            completed_count++;
        }
    }
    
    std::cout << "Total time: " << total_duration_ms << " ms" << std::endl;
    std::cout << "Processes: " << completed_count << "/" << NUM_PROCESSES << " completed" << std::endl;
    
    if (completed_count > 0) {
        std::cout << "Average time: " << (total_children_time / completed_count) << " ms" << std::endl;
    }

    return 0;
}
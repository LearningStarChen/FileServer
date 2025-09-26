#include <iostream>
#include <string>
#include <vector>
#include <unistd.h> // For fork(), execvp(), sleep()
#include <sys/wait.h> // For waitpid()
#include <cstring> // For strerror()
#include <errno.h> // For errno

// 要运行的目标程序名
const std::string APP_NAME = "./client";

int main() {
    const int NUM_PROCESSES = 5;
    std::vector<pid_t> child_pids; // 用于存储所有子进程的 PID

    std::cout << "Parent process started. PID: " << getpid() << std::endl;
    std::cout << "Spawning " << NUM_PROCESSES << " child processes to run " << APP_NAME << "..." << std::endl;

    for (int i = 0; i < NUM_PROCESSES; ++i) {
        pid_t pid = fork();

        if (pid < 0) {
            // fork() 失败
            std::cerr << "Error: fork() failed for child " << i << ". Reason: " << strerror(errno) << std::endl;
            // 可以选择继续创建下一个，或退出
            continue;
        } 
        else if (pid == 0) {
            // --- 这是子进程 ---
            std::cout << "Child process " << i << " created. My PID is: " << getpid() << std::endl;

            // 使用 execvp 来执行程序。它比 execlp 更灵活，因为它接受一个参数数组。
            // 命令和它的参数都必须作为 const char* 数组传递。
            // 数组的最后一个元素必须是 NULL，以标记结束。
            const char* argv[] = {APP_NAME.c_str(), NULL};

            // 用 my_worker_app 程序替换当前的子进程
            execvp(argv[0], const_cast<char* const*>(argv));

            // 如果 execvp 成功，下面的代码将永远不会被执行
            // 如果 execvp 失败，才会执行到这里
            std::cerr << "Error: execvp() failed for child " << i << ". Reason: " << strerror(errno) << std::endl;
            
            // 子进程执行失败，必须退出，否则它会继续执行 for 循环，创建更多的子进程！
            _exit(EXIT_FAILURE); 
        } 
        else {
            // --- 这是父进程 ---
            // fork() 返回了子进程的 PID
            child_pids.push_back(pid);
        }
    }

    // --- 父进程逻辑 ---

    // 等待所有子进程执行完毕
    std::cout << "Parent process is now waiting for all " << NUM_PROCESSES << " children to finish..." << std::endl;
    for (pid_t p : child_pids) {
        int status;
        // 等待指定的子进程 p 结束
        waitpid(p, &status, 0);
        
        // 检查子进程的退出状态
        if (WIFEXITED(status)) {
            std::cout << "Child process " << p << " finished with exit code: " << WEXITSTATUS(status) << std::endl;
        } else if (WIFSIGNALED(status)) {
            std::cout << "Child process " << p << " was killed by signal: " << WTERMSIG(status) << std::endl;
        }
    }

    std::cout << "All child processes have finished. Parent process exiting." << std::endl;

    return 0;
}
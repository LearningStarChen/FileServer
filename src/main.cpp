#include "../include/log.h"
#include "../include/server.h"
#include "../include/threadpool.h"

class LOG log("../log/logfile.txt");

void logtest() {
    LOG_TRACK << "exe at logtest function";
    LOG_DEBUG << "exe at logtest function";
    LOG_INFO << "exe at logtest function";
    LOG_WARNING << "exe at logtest function";
    LOG_ERROR << "exe at logtest function";
}

void servertest() {
    Server* ser = new Server();
    ser->start();
    //delete ser;
}

class ThreadPool* tp = nullptr;

void threadpooltest() {
    tp = new ThreadPool(10);
    // int i = 100;
    // while (i--) {
    //     tp->push([=](int a, int b) {
    //         std::cout << "Taskis running: " << i << " " << a + b << std::endl;
    //         std::this_thread::sleep_for(std::chrono::seconds(2));
    //     }, 3, 4);
    // }
    delete tp;
}



int main() {
    LOG_TRACK << "exe at main start";
    //logtest();
    //servertest();
    //threadpooltest();
    tp = new ThreadPool(10);
    servertest();
    delete tp;
    return 0;
}
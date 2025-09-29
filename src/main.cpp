#include "../include/log.h"
#include "../include/server.h"
#include "../include/threadpool.h"
#include "../include/json.h"
#include "../include/skiplist.h"

// 不要使用log，会和cmath中的对数函数相冲突的
class LOG lg("../log/logfile.txt");

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
    delete ser;
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

class JsonData* jd = nullptr;

// void jsontest(std::string jsonfilepath) {
//     JsonData jsondata(jsonfilepath);
//     std::cout << jsondata.serverport << " " << 
//     " " << jsondata.threadpoolnum << " " << " " << jsondata.clientfilestroge << std::endl;
// }

Users* users = nullptr;

int main() {
    LOG_TRACK << "exe at main start";
    //jsontest("../config/config.json");
    //logtest();
    //servertest();
    //threadpooltest();
    
    jd = new JsonData("../config/config.json");
    users = new Users(jd->skipListHigh);
    tp = new ThreadPool(jd->threadPoolNum);
    Server* ser = new Server();
    ser->start();
    delete ser;
    delete tp;
    delete jd;
    return 0;
}
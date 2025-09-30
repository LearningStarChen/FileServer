#ifndef SERVER_H
#define SERVER_H


#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <regex>

#include <unordered_set>
#include "log.h"
#include "../tool/tool.h"
#include "threadpool.h"
#include "json.h"
#include "protocol.h"
#include "skiplist.h"

extern class JsonData* jd;
extern Users* users;
extern class Server* ser;

const int MAXMESS = 2048;
const int MAX_EVENTS = 100;

class Server {
public:
    Server();
    void start();
    void stop() {
        this->stopFlag = true;
    }
private:
    int serverFd;
    //接受消息，然后解析消息
    char buffer[MAXMESS];
    int bufferlen;

    bool stopFlag;
private:
    void read_Client_Message(int fd);
    void parsing_Client_Requests(int clientfd);
private:
    
    //服务器的功能设计
    static void downloadfile(std::string filename, int clientfd); //下载文件
    static void sendmessage(std::string mess, int clientfd);      // 发送消息
    static void lookallfile(int clientfd);                        // 查看所有文件
    static void useridentity(std::string name, std::string passwd, int clientFd);   // 验证用户身份
    static void userreg(std::string name, std::string passwd, int clientFd);        // 用户注册
};

#endif
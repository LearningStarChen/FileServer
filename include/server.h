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
#include "log.h"
#include "../tool/tool.h"
#include "threadpool.h"

const int MAXMESS = 1024;
const int MAX_EVENTS = 100;

class Server {
public:
    Server();
    void start();
private:
    int serverFd;
    //接受消息，然后解析消息
    char buffer[MAXMESS];
    int bufferlen;
private:
    void read_Client_Message(int fd);
    void parsing_Client_Requests(int clientfd);
private:
    //服务器的功能设计
    static void downloadfile(std::string mess);
    // void sendmessage();
    // void lookallfile();
};


#endif
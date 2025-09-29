#ifndef TOOL_H
#define TOOL_H

#include <string>
#include <iostream>
#include <fstream>
#include <mutex>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <cstring>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <sys/stat.h>


class Tool {
public:
    static std::string getTimestamp();
    static int setNonBlocking(int fd);
    static size_t getFileSize(const std::string& filepath);
    // 自己实现unescapeString函数
    static std::string unescapeString(const std::string& input);
};

#endif


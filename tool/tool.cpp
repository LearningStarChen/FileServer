#include "tool.h"

std::string Tool::getTimestamp() {
    std::time_t now = std::time(nullptr);
    char buffer[20];
    std::strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    return std::string(buffer);
}



int Tool::setNonBlocking(int fd) {
    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        std::cout << "setNonBlocking fcntl failed!" << std::endl;
        exit(-1);
    }
    flags |= O_NONBLOCK;
    return fcntl(fd, F_SETFL, flags);
}

size_t Tool::getFileSize(const std::string& filePath) {
    struct stat statBuf; // 定义 stat 结构体
    if (stat(filePath.c_str(), &statBuf) == 0) {
        return statBuf.st_size; // 返回文件大小
    } else {
        std::cout << "Error getting file size" << std::endl; // 输出错误信息
        return 0;
    }
}
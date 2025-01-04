#include <iostream>
#include <sys/stat.h> // 包含 stat 的头文件

size_t getFileSize(const std::string& filePath) {
    struct stat statBuf; // 定义 stat 结构体
    if (stat(filePath.c_str(), &statBuf) == 0) {
        return statBuf.st_size; // 返回文件大小
    } else {
        perror("Error getting file size"); // 输出错误信息
        return 0;
    }
}

int main() {
    std::string filePath = "git.pdf"; // 文件路径
    size_t fileSize = getFileSize(filePath);

    if (fileSize > 0) {
        std::cout << "File size: " << fileSize << " bytes" << std::endl;
    } else {
        std::cout << "Failed to get file size." << std::endl;
    }

    return 0;
}

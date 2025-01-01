#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 4096;

uint32_t calculateChecksum(const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    uint32_t checksum = 0;
    char ch;
    while (inFile.get(ch)) {
        checksum += static_cast<uint8_t>(ch);
    }
    inFile.close();
    return checksum;
}

void sendFile(int socket, const std::string& filePath) {
    std::ifstream inFile(filePath, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << filePath << std::endl;
        return;
    }

    // 获取文件名和大小
    std::string fileName = filePath.substr(filePath.find_last_of("/\\") + 1);
    inFile.seekg(0, std::ios::end);
    uint64_t fileSize = inFile.tellg();
    inFile.seekg(0, std::ios::beg);

    // 1. 发送协议头
    uint32_t fileNameLen = fileName.size();
    send(socket, &fileNameLen, sizeof(fileNameLen), 0);
    send(socket, fileName.c_str(), fileName.size(), 0);
    send(socket, &fileSize, sizeof(fileSize), 0);

    // 2. 分块发送文件数据
    char buffer[BUFFER_SIZE];
    uint64_t bytesSent = 0;
    uint32_t checksum = 0;
    while (bytesSent < fileSize) {
        inFile.read(buffer, BUFFER_SIZE);
        std::streamsize bytesRead = inFile.gcount();
        send(socket, buffer, bytesRead, 0);

        // 计算校验和
        for (std::streamsize i = 0; i < bytesRead; ++i) {
            checksum += static_cast<uint8_t>(buffer[i]);
        }

        bytesSent += bytesRead;
    }

    // 3. 发送协议尾
    send(socket, &checksum, sizeof(checksum), 0);

    inFile.close();
    std::cout << "File sent successfully: " << filePath << std::endl;
}

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // 创建套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 连接到服务器
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);

    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Connection failed");
        return 1;
    }

    // 发送文件
    std::string filePath;
    std::cout << "Enter file path: ";
    std::cin >> filePath;
    sendFile(clientSocket, filePath);

    close(clientSocket);
    return 0;
}

#include <iostream>
#include <fstream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

const int PORT = 8080;
const int BUFFER_SIZE = 4096;

void receiveFile(int clientSocket) {
    char buffer[BUFFER_SIZE];

    // 1. 接收协议头
    uint32_t fileNameLen;
    read(clientSocket, &fileNameLen, sizeof(fileNameLen));

    char fileName[256];
    read(clientSocket, fileName, fileNameLen);
    fileName[fileNameLen] = '\0';

    uint64_t fileSize;
    read(clientSocket, &fileSize, sizeof(fileSize));

    std::cout << "Receiving file: " << fileName << " (" << fileSize << " bytes)" << std::endl;

    // 2. 打开文件保存
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    // 3. 接收文件数据
    uint64_t bytesReceived = 0;
    uint32_t checksum = 0;
    while (bytesReceived < fileSize) {
        ssize_t bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
        if (bytesRead <= 0) break;

        outFile.write(buffer, bytesRead);
        bytesReceived += bytesRead;

        // 计算校验和
        for (ssize_t i = 0; i < bytesRead; ++i) {
            checksum += static_cast<uint8_t>(buffer[i]);
        }
    }
    outFile.close();

    // 4. 接收协议尾
    uint32_t receivedChecksum;
    read(clientSocket, &receivedChecksum, sizeof(receivedChecksum));

    if (checksum == receivedChecksum) {
        std::cout << "File received successfully and checksum verified!" << std::endl;
    } else {
        std::cerr << "Checksum verification failed!" << std::endl;
    }
}

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // 创建套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("Socket creation failed");
        return 1;
    }

    // 绑定地址和端口
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        return 1;
    }

    // 监听
    if (listen(serverSocket, 5) < 0) {
        perror("Listen failed");
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    // 接受客户端连接
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
    if (clientSocket < 0) {
        perror("Accept failed");
        return 1;
    }

    // 接收文件
    receiveFile(clientSocket);

    close(clientSocket);
    close(serverSocket);
    return 0;
}

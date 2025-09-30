
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1000

int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        perror("Invalid address");
        close(clientSocket);
        return EXIT_FAILURE;
    }

    // 连接服务器
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        close(clientSocket);
        return EXIT_FAILURE;
    }

    std::cout << "Connected to server.\n";

    // std::cout << "请输入文件的名称" << std::endl;
    // std::string filename;
    // std::cin >> filename;
    std::string request[2] = {
        R"({
            "name": "chn",
            "type": 4,
            "passwd":"123456"
        })",
        R"({
            "name": "czp",
            "type": 4,
            "passwd":"456789"
        })"
    };
    // std::cout << request.c_str()<< std::endl;
    // std::cout << request.size() << std::endl;
    for (int i = 0; i < 2; i++)
        write(clientSocket, request[i].c_str(), request[i].size());
    // 接收文件大小
    char buffer[BUFFER_SIZE];
    ssize_t bytesRead = recv(clientSocket, &buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
        perror("Error receiving file size");
        close(clientSocket);
        return EXIT_FAILURE;
    }
    std::cout << std::string(buffer) << std::endl;
    close(clientSocket);

    return EXIT_SUCCESS;
}

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    // 创建服务器套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Error creating socket");
        return EXIT_FAILURE;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    // 绑定地址和端口
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error binding socket");
        close(serverSocket);
        return EXIT_FAILURE;
    }

    // 监听连接
    if (listen(serverSocket, 1) == -1) {
        perror("Error listening on socket");
        close(serverSocket);
        return EXIT_FAILURE;
    }

    std::cout << "Server listening on port " << PORT << "...\n";

    // 接受客户端连接
    clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket == -1) {
        perror("Error accepting connection");
        close(serverSocket);
        return EXIT_FAILURE;
    }

    std::cout << "Client connected.\n";

    // 打开要发送的文件
    std::ifstream inputFile("123456.txt", std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Error: Cannot open file 'file_to_send.txt'" << std::endl;
        close(clientSocket);
        close(serverSocket);
        return EXIT_FAILURE;
    }

    // 获取文件大小
    inputFile.seekg(0, std::ios::end);
    size_t fileSize = inputFile.tellg();
    inputFile.seekg(0, std::ios::beg);

    // 发送文件大小
    ssize_t bytesSent = send(clientSocket, &fileSize, sizeof(fileSize), 0);
    if (bytesSent == -1) {
        perror("Error sending file size");
        close(clientSocket);
        close(serverSocket);
        return EXIT_FAILURE;
    }
    std::cout << "File size sent: " << fileSize << " bytes\n";

    // 发送文件内容
    char buffer[BUFFER_SIZE];
    size_t totalBytesSent = 0;

    while (!inputFile.eof()) {
        inputFile.read(buffer, sizeof(buffer));
        ssize_t bytesToSend = inputFile.gcount();

        bytesSent = send(clientSocket, buffer, bytesToSend, 0);
        if (bytesSent == -1) {
            perror("Error sending file data");
            break;
        }
        totalBytesSent += bytesSent;
        std::cout << "Sent " << bytesSent << " bytes, total: " << totalBytesSent << " bytes\n";
    }

    std::cout << "File sent successfully, total bytes: " << totalBytesSent << "\n";

    // 保持连接状态，继续等待其他操作（如果需要）
    std::cout << "Connection with client remains open.\n";

    // 关闭文件和套接字
    inputFile.close();
    close(clientSocket);
    close(serverSocket);

    return EXIT_SUCCESS;
}

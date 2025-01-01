#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

// void handleClient(int clientSocket) {
//     char buffer[BUFFER_SIZE] = {0};

//     // 读取客户端请求
//     int bytesRead = read(clientSocket, buffer, BUFFER_SIZE);
//     if (bytesRead <= 0) {
//         std::cerr << "Failed to read request from client." << std::endl;
//         close(clientSocket);
//         return;
//     }

//     std::string requestedFile(buffer);
//     std::cout << "Client requested file: " << requestedFile << std::endl;

//     // 打开文件
//     std::ifstream inFile(requestedFile, std::ios::binary);
//     if (!inFile.is_open()) {
//         std::cerr << "File not found: " << requestedFile << std::endl;
//         close(clientSocket);
//         return;
//     }

//     // 发送文件内容
//     while (!inFile.eof()) {
//         inFile.read(buffer, BUFFER_SIZE);  // 读取文件内容到缓冲区
//         send(clientSocket, buffer, inFile.gcount(), 0);  // 发送读取的内容
//     }

//     std::cout << "File sent successfully." << std::endl;

//     inFile.close();
//     close(clientSocket);
// }

void handleClient(int clientSocket) {
    char buffer[BUFFER_SIZE] = {0};

    // 读取客户端请求，可以改成读取的文件先行的协议信息
    int bytesRead = read(clientSocket, buffer, BUFFER_SIZE); // 使用 read
    if (bytesRead <= 0) {
        std::cerr << "Failed to read request from client." << std::endl;
        close(clientSocket);
        return;
    }

    std::string requestedFile(buffer);
    std::cout << "Client requested file: " << requestedFile << std::endl;

    // 打开文件
    std::ifstream inFile(requestedFile, std::ios::binary);
    if (!inFile.is_open()) {
        std::cerr << "File not found: " << requestedFile << std::endl;
        close(clientSocket);
        return;
    }

    // 发送文件内容
    while (!inFile.eof()) {
        inFile.read(buffer, BUFFER_SIZE);  // 读取文件内容到缓冲区
        write(clientSocket, buffer, inFile.gcount());  // 使用 write
    }

    std::cout << "File sent successfully." << std::endl;

    inFile.close();
    close(clientSocket);
}


int main() {
    int serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addrLen = sizeof(clientAddr);

    // 创建服务器套接字
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // 绑定地址和端口
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Bind failed");
        return -1;
    }

    // 开始监听
    if (listen(serverSocket, 5) == -1) {
        perror("Listen failed");
        return -1;
    }
    std::cout << "Server is listening on port " << PORT << "..." << std::endl;

    // 接收客户端连接并处理请求
    while (true) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &addrLen);
        if (clientSocket == -1) {
            perror("Accept failed");
            continue;
        }
        std::cout << "Client connected." << std::endl;

        // 处理客户端请求
        handleClient(clientSocket);
    }

    close(serverSocket);
    return 0;
}

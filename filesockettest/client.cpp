#include <iostream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 12345
#define BUFFER_SIZE 1024

// void requestFile(int socket, const std::string& filename) {
//     // 发送请求文件名给服务端
//     send(socket, filename.c_str(), filename.size(), 0);

//     // 接收文件内容并保存
//     char buffer[BUFFER_SIZE] = {0};
//     std::ofstream outFile("received_" + filename, std::ios::binary);
//     if (!outFile.is_open()) {
//         std::cerr << "Failed to open file for writing." << std::endl;
//         return;
//     }

//     int bytesRead;
//     while ((bytesRead = read(socket, buffer, BUFFER_SIZE)) > 0) {
//         outFile.write(buffer, bytesRead);  // 写入文件内容
//     }

//     std::cout << "File received and saved as: received_" << filename << std::endl;

//     outFile.close();
// }
//######采用二进制的方式读取文件，防止文件被\r\n等所破坏，特别是传输非文本文件，例如图片，视频等#######
void requestFile(int socket, const std::string& filename) {
    // 发送请求文件名给服务端，改成文件的协议的组织
    write(socket, filename.c_str(), filename.size()); // 使用 write

    // 接收文件内容并保存
    char buffer[BUFFER_SIZE] = {0};
    std::ofstream outFile("received_" + filename, std::ios::binary);
    if (!outFile.is_open()) {
        std::cerr << "Failed to open file for writing." << std::endl;
        return;
    }

    int bytesRead;
    while ((bytesRead = read(socket, buffer, BUFFER_SIZE)) > 0) { // 使用 read
        outFile.write(buffer, bytesRead);  // 写入文件内容
    }

    std::cout << "File received and saved as: received_" << filename << std::endl;

    outFile.close();
}



int main() {
    int clientSocket;
    struct sockaddr_in serverAddr;

    // 创建客户端套接字
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) {
        perror("Socket creation failed");
        return -1;
    }

    // 连接到服务器
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Connect failed");
        return -1;
    }

    std::cout << "Connected to server." << std::endl;

    // 请求文件
    std::string filename;
    std::cout << "Enter the filename to request: ";
    std::cin >> filename;
    requestFile(clientSocket, filename);

    close(clientSocket);
    return 0;
}

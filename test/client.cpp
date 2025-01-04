// #include <iostream>
// #include <fstream>
// #include <cstring>
// #include <cstdlib>
// #include <unistd.h>
// #include <arpa/inet.h>


// void recvfile() {
    

//     int clientfd = socket(AF_INET, SOCK_STREAM, 0);
//     if (clientfd == -1) {
//         perror("Error creating socket");
//         return ;
//     }
//     struct sockaddr_in serverAddr;
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(12345);
//     serverAddr.sin_addr.s_addr = INADDR_ANY;

//     if (connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
//         perror("Error connecting to server");
//         close(clientfd);
//         return ;
//     }
//     std::string request = "downloadfile,";
//     std::cout << "请输入想要接受的文件的名称：" << std::endl;
//     std::string filename;
//     std::cin >> filename;
//     request += filename;

//     write(clientfd, request.c_str(), request.size());

//     char buffer[1024];
//     int recvsize = read(clientfd, buffer, sizeof(buffer));
    
//     std::cout << "文件的大小是：" << std::string(buffer, recvsize) << std::endl;
//     size_t filesize = atoi(std::string(buffer, recvsize).c_str());


//     std::ofstream outputFile("received_file.txt", std::ios::binary);
//     if (!outputFile.is_open()) {
//         std::cerr << "Error: Cannot open file to write\n";
//         close(clientfd);
//         return;
//     }

//     //char buffer[1024];
//     ssize_t bytesRead;
//     size_t total = 0;

//     while (total < filesize) {
//         bytesRead = recv(clientfd, buffer, sizeof(buffer), 0);
//         if (bytesRead > 0) {
//             outputFile.write(buffer, bytesRead);
//             total += bytesRead;
//         }
//     }
// }



// int main() {
//     recvfile();
//     return 0;
// }
#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

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

    // 接收文件大小
    size_t fileSize;
    ssize_t bytesRead = recv(clientSocket, &fileSize, sizeof(fileSize), 0);
    if (bytesRead <= 0) {
        perror("Error receiving file size");
        close(clientSocket);
        return EXIT_FAILURE;
    }
    std::cout << "File size received: " << fileSize << " bytes\n";

    // 接收文件内容
    std::ofstream outputFile("received_file.txt", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Cannot open file to write\n";
        close(clientSocket);
        return EXIT_FAILURE;
    }

    char buffer[BUFFER_SIZE];
    size_t totalBytesReceived = 0;

    while (totalBytesReceived < fileSize) {
        bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesRead > 0) {
            outputFile.write(buffer, bytesRead);
            totalBytesReceived += bytesRead;
            std::cout << "Received " << bytesRead << " bytes, total: " << totalBytesReceived << " bytes\n";
        } else if (bytesRead == 0) {
            std::cerr << "Server closed the connection unexpectedly.\n";
            break;
        } else {
            perror("Error receiving file data");
            break;
        }
    }

    if (totalBytesReceived == fileSize) {
        std::cout << "File received successfully, total bytes: " << totalBytesReceived << "\n";
    } else {
        std::cerr << "File transfer incomplete.\n";
    }

    // 保持连接状态，等待进一步指令（如果需要）

    // 关闭文件和套接字
    outputFile.close();
    close(clientSocket);

    return EXIT_SUCCESS;
}

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>


void recvfile() {
    

    int clientfd = socket(AF_INET, SOCK_STREAM, 0);
    if (clientfd == -1) {
        perror("Error creating socket");
        return ;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (connect(clientfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) {
        perror("Error connecting to server");
        close(clientfd);
        return ;
    }
    std::string request = "downloadfile,";
    std::cout << "请输入想要接受的文件的名称：" << std::endl;
    std::string filename;
    std::cin >> filename;
    request += filename;

    write(clientfd, request.c_str(), request.size());

    char buffer[1024];
    int recvsize = read(clientfd, buffer, sizeof(buffer));
    
    std::cout << "文件的大小是：" << std::string(buffer, recvsize) << std::endl;

}

int main() {
    recvfile();
    return 0;
}

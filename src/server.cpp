#include "../include/server.h"


extern class ThreadPool* tp;

Server::Server() {
    LOG_TRACK << "server at constructor function start";
    // 创建服务器套接字
    serverFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    if (serverFd == -1) {
        LOG_ERROR << "server at create socket function failed";
        exit(-1);
    }
    //设置端口复用
    int opt = 1;
    if (setsockopt(serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        LOG_ERROR << "server at SO_REUSEADDR failed";
        close(serverFd);
        exit(-1);
    }

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(12345);

    if (bind(serverFd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
        LOG_ERROR << "server at bind function failed";
        close(serverFd);
        exit(-1);
    }

    if (listen(serverFd, 10) == -1) {
        LOG_ERROR << "server at listen function failed";
        close(serverFd);
        exit(-1);
    }
    LOG_TRACK << "server start successful";
}

void Server::start() {
    // 创建 epoll 实例
    int epollFd = epoll_create1(0);
    if (epollFd == -1) {
        LOG_ERROR << "epoll_create1 failed";
        return;
    }

    // 将服务器套接字添加到 epoll 中
    struct epoll_event event;
    event.data.fd = serverFd;
    event.events = EPOLLIN;
    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, serverFd, &event) == -1) {
        LOG_ERROR << "epoll_ctl failed";
        close(epollFd);
        return;
    }

    // 事件循环
    struct epoll_event events[MAX_EVENTS];
    while (1) {
        int nfds = epoll_wait(epollFd, events, MAX_EVENTS, -1);
        if (nfds == -1) {
            LOG_ERROR << "epoll_wait failed";
            break;
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == serverFd) {
                // 新客户端连接
                int clientFd = accept(serverFd, NULL, NULL);
                if (clientFd == -1) {
                    LOG_ERROR << "accept failed";
                    continue;
                }

                // 设置非阻塞，ET模式下必须设置非阻塞
                if (Tool::setNonBlocking(clientFd) == -1) {
                    LOG_ERROR << "setNonBlocking failed";
                    close(clientFd);
                    continue;
                }

                // 将客户端套接字添加到 epoll 中
                event.data.fd = clientFd;
                event.events = EPOLLIN | EPOLLET; //边缘触发模式
                if (epoll_ctl(epollFd, EPOLL_CTL_ADD, clientFd, &event) == -1) {
                    LOG_ERROR << "epoll_ctl failed";
                    close(clientFd);
                }
                LOG_TRACK << "new client fd" << clientFd << "already connect server";

            } else if (events[n].events & EPOLLIN){
                //正常情况下这里会触发三次（如果规范的话），第一次，读取到数据，第二次，读到-1那么表示读完，第三次，读到0，表示对端关闭；
                // static int a = 0;
                // std::cout << a++ << std::endl;
                //读取然后接受客户端消息
                read_Client_Message(events[n].data.fd);
                // 处理完请求后关闭连接
            }
        }
    }

    close(epollFd);
}

// void Server::read_Client_Message(int fd) {
//     //连接和发送消息都会触发
//     char buffer[1024];
//     while (true) {
//         ssize_t n = read(fd, buffer, sizeof(buffer)); // 读取数据
//         if (n == -1) { // 错误情况
//             if (errno == EAGAIN) {
//                 // 表示数据读取完毕，没有更多数据
//                 break;
//             }
//             LOG_ERROR << "read from client fd: " << fd <<" error";
//             close(fd); // 关闭文件描述符
//             break;
//         } else if (n == 0) {
//             // 对端关闭连接
//             LOG_WARNING << "client fd " << fd << " connection closed by peer";
//             close(fd);
//             break;
//         } else {
//             // 正常将数据得到存储于buffer
            
//         }
//     }
//     std::cout << "recv from client" << buffer << std::endl;
    
// }

void Server::read_Client_Message(int clientfd) {
    bufferlen = 0;
    while (true) {
        ssize_t n = read(clientfd, buffer + bufferlen, sizeof(buffer) - bufferlen);
        if (n > 0) {
            bufferlen += n;
            continue; // 继续读取剩余数据
        } else if (n == 0) {
            LOG_WARNING << "client fd " << clientfd << " connection closed by peer";
            epoll_ctl(serverFd, EPOLL_CTL_DEL, clientfd, nullptr);
            close(clientfd);
            break;
        } else if (n == -1) {
            if (errno == EAGAIN || errno == EWOULDBLOCK) {
                LOG_TRACK << "read client info finished";
                break; // 数据读取完毕，退出循环
            } else {
                LOG_ERROR << "read from client fd: " << clientfd << " error: " << strerror(errno);
                epoll_ctl(serverFd, EPOLL_CTL_DEL, clientfd, nullptr);
                close(clientfd);
                break;
            }
        }
    }
    parsing_Client_Requests(clientfd); // 在循环外统一处理解析
}



void Server::parsing_Client_Requests(int clientfd) {
    LOG_TRACK << "parsing client requests";
    //std::cout << std::string(buffer, bufferlen) << std::endl;
    std::string message_from_client = std::string(buffer, bufferlen);
    std::cout << message_from_client << std::endl;

    // 1. 下载文件：
    // downloadfile,filename.txt(pdf,other formats)
    // 2. 发送消息给另一用户：
    // sendmessage,message(string formats),otherclientfd
    // 3. 查看所有文件（暂时先不考虑用户隔离）
    // lookallfile
    if (message_from_client.find("downloadfile") != std::string::npos) {
        LOG_TRACK << "message formats is downloadfile";
        //std::cout << message_from_client << std::endl;
        
        tp->push(downloadfile, message_from_client, clientfd);


    } else if (message_from_client.find("sendmessage") != std::string::npos) {
        LOG_TRACK << "message formats is sendmessage";
        //std::cout << message_from_client << std::endl;
        tp->push(sendmessage, message_from_client, clientfd);

    } else if (message_from_client.find("lookallfile") != std::string::npos) {
        LOG_TRACK << "message formats is lookallfile";
        //std::cout << message_from_client << std::endl;
        tp->push(lookallfile, message_from_client, clientfd);

    }
    // std::regex pattern(R"(([^,]+),(.+))"); // 匹配逗号分隔的两个部分
    // std::smatch match; // 用于存储匹配结果

    // if (std::regex_match(message_from_client, match, pattern)) {
    //     // match[1] 是第一个部分，match[2] 是第二个部分
    //     std::string part1 = match[1];
    //     std::string part2 = match[2];

    //     // 输出结果
    //     std::cout << "Part 1: " << part1 << std::endl;
    //     std::cout << "Part 2: " << part2 << std::endl;
    // } else {
    //     std::cerr << "Invalid input format!" << std::endl;
    // }



}


void Server::downloadfile(std::string mess, int client) {
    std::cout << "到了down函数内部"  << mess << std::endl;
}

void Server::sendmessage(std::string mess, int client) {
    std::cout << "到了sendmessage函数内部"  << mess << std::endl;
}

void Server::lookallfile(std::string mess, int client) {
    std::cout << "到了lookallfile函数内部"  << mess << std::endl;
}

# 生成运行
1. 创建 build/ 文件夹: 在项目根目录下执行：
mkdir build
cd build
2. 运行 CMake: 在 build/ 文件夹中运行：
cmake ..
3. 构建项目: 运行以下命令来构建可执行文件：
cmake --build .
4. 运行生成的可执行文件: 生成的可执行文件位于 bin/ 文件夹：
./bin/FileServer


# 需要考虑配置的量
1. 服务器绑定的端口
2. 日志的文件路径（如果没有添加默认的路径./log/logfile.txt）
3. MAX_EVENT， epoll每次最多可以处理的最大事件数量
4. 线程池开辟的线程数量
5. 服务端接受客户端的消息的最大长度MAXMESS
6. 服务器的文件存储区域（存储文件的目录）的地址
7. 所存储的文件所在的地址


# 客户端与服务端的交互格式：
1. 下载文件：
   downloadfile,filename.txt(pdf, other formats)
2. 发送消息给另一用户：
   sendmessage,message(string formats),otherclientfd
3. 查看所有文件（暂时先不考虑用户隔离）
   lookallfile,
# 还未干的事情
1. 增加shell一步构建执行
2. 增加config类读取配置文件，（由于本项目不借助任何第三方工具，故用txt配置项目）
3. 将文件的读写和消息的发送逻辑合并进server.h中


# 大文件下载测试
1. 下载文件测试成功
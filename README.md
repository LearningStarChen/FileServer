一、生成运行
1. 创建 build/ 文件夹: 在项目根目录下执行：
mkdir build
cd build
2. 运行 CMake: 在 build/ 文件夹中运行：
cmake ..
3. 构建项目: 运行以下命令来构建可执行文件：
cmake --build .
4. 运行生成的可执行文件: 生成的可执行文件位于 bin/ 文件夹：
./bin/FileServer


二、需要考虑配置的量
1. 服务器绑定的端口
2. 日志的文件路径（如果没有添加默认的路径./log/logfile.txt）
3. MAX_EVENT， epoll每次最多可以处理的最大事件数量
4. 线程池开辟的线程数量
5. 服务端接受客户端的消息的最大长度MAXMESS


三、客户端与服务端的交互格式：
1. 下载文件：
   downloadfile,filename.txt(pdf, other formats)
2. 发送消息给另一用户：
   sendmessage,message(string formats),otherclientfd
3. 查看所有文件（暂时先不考虑用户隔离）
   lookallfile,
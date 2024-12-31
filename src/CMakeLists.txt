# Set source files
# set(SOURCE_FILES
#     main.cpp
#     server.cpp
# )
#file(GLOB SOURCE_FILES "${PROJECT_SOURCE_DIR}/src/*.cpp")

# src/CMakeLists.txt

# 定义 FileServer 的源文件
set(SOURCE_FILES
    main.cpp
    server.cpp
    threadpool.cpp
)

#################################必须先生成exe在链接库
# 创建可执行文件 FileServer
add_executable(FileServer ${SOURCE_FILES})
# 链接 ToolLib 静态库
target_link_libraries(FileServer PUBLIC ToolLib)
# 链接线程库到可执行文件
find_package(Threads REQUIRED)
target_link_libraries(FileServer PUBLIC ToolLib Threads::Threads)





# # Add library for tools
# set(TOOL_FILES
#     tool.h
# )

# # Create a static library for the tool functions
# add_library(ToolLib STATIC ${TOOL_FILES})

# # Include directories for the tool library
# target_include_directories(ToolLib PUBLIC ${PROJECT_SOURCE_DIR}/tool)


# 定义 ToolLib 库，使用 tool.cpp
add_library(ToolLib STATIC tool.cpp)

# 指定头文件路径，供其他目标使用
target_include_directories(ToolLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)

# 设置库的属性
set_target_properties(ToolLib PROPERTIES CXX_STANDARD 11 CXX_STANDARD_REQUIRED YES)

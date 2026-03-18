# QGranView - A Granite Viewer Application
cmake_minimum_required(VERSION 3.10)
project(QGranView)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 使用 Granite 的便捷函数创建应用程序
add_granite_application(qgranview src/main.cpp)

# 设置资产目录（如果需要的话）
if (NOT ANDROID)
    target_compile_definitions(qgranview PRIVATE ASSET_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/assets")
endif()

# 如果需要链接额外的库，可以在这里添加
# target_link_libraries(qgranview PRIVATE granite-video) # 示例：如果需要视频功能
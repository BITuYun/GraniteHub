# QGranView - A Granite Viewer Application with Qt Integration
cmake_minimum_required(VERSION 3.10)
project(QGranView)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找 Qt 包
find_package(Qt6 COMPONENTS Core Widgets OpenGL QUIET)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
endif()

# 设置源文件路径（在 src/ 目录下）
set(QGranView_SOURCES
    src/main.cpp
    src/qgranview_window.cpp
)

set(QGranView_HEADERS
    src/qgranview_window.h
)

# 如果使用 Qt5 或 Qt6，启用自动 MOC
if(Qt6_FOUND)
    qt6_standard_project_setup()
    qt6_add_executable(qgranview ${QGranView_SOURCES} ${QGranView_HEADERS})
    target_link_libraries(qgranview Qt6::Core Qt6::Widgets Qt6::OpenGL)
elseif(Qt5_FOUND)
    set(CMAKE_AUTOMOC ON)
    set(CMAKE_AUTORCC ON)
    set(CMAKE_AUTOUIC ON)
    add_executable(qgranview ${QGranView_SOURCES} ${QGranView_HEADERS})
    target_link_libraries(qgranview Qt5::Core Qt5::Widgets Qt5::OpenGL)
endif()

# 设置 Granite 应用程序定义
if (NOT ANDROID)
    target_compile_definitions(qgranview PRIVATE ASSET_DIRECTORY="${CMAKE_CURRENT_SOURCE_DIR}/assets")
endif()
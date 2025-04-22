cmake_minimum_required(VERSION 3.10)

# 项目名称
project(DSAProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 添加源文件
add_executable(SortExecutable
    main.cpp

)

# 包含头文件目录
target_include_directories(SortExecutable PRIVATE ${CMAKE_SOURCE_DIR})

#cmake -S . -B build
#cmake --build build
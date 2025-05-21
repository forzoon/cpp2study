cmake_minimum_required(VERSION 3.10)

# 项目名称
project(DSAProject)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 添加源文件
add_executable(Main
    main.cpp
        Test/vector_test.cpp
        MySTL/Vector.cpp

)

# 包含头文件目录
target_include_directories(Main PRIVATE
        ${CMAKE_SOURCE_DIR}
        ${CMAKE_SOURCE_DIR}/MySTL
        ${CMAKE_SOURCE_DIR}/Test
        )

#cmake -S . -B build
#cmake --build build
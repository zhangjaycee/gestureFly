cmake_minimum_required(VERSION 2.8)

#解决方案的名字
project(gestureFly)

#添加源文件
#命令语法：aux_source_directory(<dir> <variable>)
#命令简述：用于将 dir 目录下的所有源文件的名字保存在变量 variable 中
aux_source_directory( src SRC_LIST )

find_package(OpenCV REQUIRED)

#生成exe
add_executable( flybin ${SRC_LIST} )

target_link_libraries( flybin ${OpenCV_LIBS} )

#添加包含的头文件（如果需要的话）
#include_directories( /usr/local/include )
#include_directories( /usr/local/include/opencv )
#include_directories( /usr/local/include/opencv2 )


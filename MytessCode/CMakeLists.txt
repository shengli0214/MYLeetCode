
cmake_minimum_required(VERSION 3.10)
# set(CMAKE_C_COMPILE "C:\\MinGW\\bin\\gcc.exe")
# set(CMAKE_CXX_COMPILE "C:\\MinGW\\bin\\g++.exe")
project(Demo1)
# add_executable(Demo test.cpp) 将test.cpp的源文件编译为一个名称为Demo的可执行文件
# aux_source_directory(<dir> <variable)
#查找当前目录下的所有源文件并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)
# 指定生成目标
add_executable(test ${DIR_SRCS})


#多个目录,多个源文件  需要在每个目录各编写一个CMakeList.txt文件.
# add_subdirectory(math)

#指定生成目标 


#添加动态链接库
# target_link_libraries(Demo MathFunctions)

#子目录 中的CMakeList.txt
# aux_source_directory(. DIR_LIB_SRCS)
#生成链接库
# add_library(MathFunctions ${DIR_LIB_SRCS})

#自定义编译选项
# configure_file(
#     "${PROJECT_SOURCE_DIR}/config.h.in"
#     "${PROJECT_BINARY_DIR}/config.h"
# )

#是否使用自己的MathFunctions库
# option(USE_MYMATH 
# "Use provided math implementation" ON)
#是否加入MathFunctions库
# if(USE_MYMATH)
# include_directories("${PROJECT_SOURCE_DIR}/math")
# add_subdirectory(math)
# set(EXTRA_LIB ${EXTRA_LIBS}MathFunctions)
# endif(USE_MYMATH)

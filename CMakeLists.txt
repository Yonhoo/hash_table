cmake_minimum_required(VERSION 3.0)
project(hashtable)

set(CMAKE_CXX_FLAGS "-std=c++11  -Wall -Ofast")


#查找src下的所有源文件
aux_source_directory(. DIR_LIB_SRCS)

include_directories(. DIR_INC_SRCS)

add_executable(hashtable hashtable.cpp  hashtable.h hash_table_iterator.h)





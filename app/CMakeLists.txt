cmake_minimum_required(VERSION 3.4.1)

# 设置变量
set(distribution_dir ../../../../libs )

# 查找系统库 liblog.so
find_library(   log-lib
                log )

# 添加库  动态导入
add_library(    fmod
                SHARED
                 IMPORTED )

# 设置库路径   ANDROID_ABI 自动赋予值
set_target_properties(  fmod
                        PROPERTIES IMPORTED_LOCATION
                        ${distribution_dir}/${ANDROID_ABI}/libfmod.so)

add_library(    fmodL
                SHARED
                IMPORTED )

set_target_properties(  fmodL
                        PROPERTIES IMPORTED_LOCATION
                        ${distribution_dir}/${ANDROID_ABI}/libfmodL.so)

# 使用C++ 11 标准
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")


# 引入单个cpp文件
add_library(    changevoice
                SHARED
                src/main/cpp/ChangeVoice.cpp )

# 引入头文件
include_directories(src/main/cpp/inc)

# 关联库
target_link_libraries(  changevoice
                        fmod
                        fmodL
                        ${log-lib} )

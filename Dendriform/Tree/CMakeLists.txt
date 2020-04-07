cmake_minimum_required(VERSION 3.0.0)

#指定工程的名称(可与文件夹名称不同，但为了此文件的普适性，设置为相同)
project(Tree)

#添加include路径(这样就可以找到头文件)
include_directories(${PROJECT_SOURCE_DIR}/Lib)

#将源文件输出到可执行文件（这个执行的是build任务？）
add_executable(${PROJECT_NAME} ${PROJECT_NAME}.cpp Lib/Small_Tricks.cpp)

#进入断点的debug模式
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")


#以下均为不需要的语句

#将可执行文件输出到build目录下(默认就是build,可以改到需要输出的地方)
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build)

#添加Lib子目录,这样lib中的cmakelists文件也会被处理（好像不必要）
#add_subdirectory(Lib)

#查找当前目录下的所有源文件，并将名称保存到DIR_ROOT_SRCS变量(然而事实并非如此，但是为什么呢？)
#aux_source_directory(. DIR_ROOT_SRCS)

#编译完之后添加链接库，指明可执行文件main需要的链接库（前面已经将链接库名称保存到DIR_ROOT_SRCS）
#target_link_libraries(${PROJECT_NAME} ${DIR_ROOT_SRCS})
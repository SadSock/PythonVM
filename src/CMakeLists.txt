# 设置运行此配置文件所需的CMake最低版本
cmake_minimum_required(VERSION 3.15)

# set the project name
# 设置项目名称
project(stone VERSION 1.0)

# specify the C++ standard
# 指定C ++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)



set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")


# 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# configure a header file to pass some of the CMake settings
# to the source code
# 配置头文件以将某些CMake设置传递给源代码
configure_file(stoneConfig.h.in stoneConfig.h)



#查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加

SET(CMAKE_PREFIX_PATH  "/usr/local/Cellar/qt/5.14.2/")
#find_package(Qt5Widgets)
find_package(Qt5Core)
#find_package(Qt5Gui)


# add_library(token token.hpp)
# target_link_libraries(stone PUBLIC Token)


# add the executable
# 添加一个可执行文件
add_executable(stone stone.cpp
  object/hiInteger.hpp
  object/hiString.hpp
  util/arrayList.hpp
  code/binaryFileParser.hpp
  code/codeObject.hpp)

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
# 将二进制目录添加到包含文件的搜索路径中，以便我们找到TutorialConfig.h
target_include_directories(stone PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#添加Qt5依赖项
#target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Core)







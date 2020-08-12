# 设置运行此配置文件所需的CMake最低版本
cmake_minimum_required(VERSION 3.15)

#set(CMAKE_C_COMPILER /usr/bin/gcc)
#set(CMAKE_CXX_COMPILER /usr/bin/g++)
set(CMAKE_C_COMPILER "/usr/local/opt/llvm/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++")


# set the project name
# 设置项目名称
project(stone VERSION 1.0)

# specify the C++ standard
# 指定C ++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)




# 
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# configure a header file to pass some of the CMake settings
# to the source code
# 配置头文件以将某些CMake设置传递给源代码
configure_file(stoneConfig.h.in stoneConfig.h)



#查找需要的Qt库文件，最好每一个库都要写，Qt也会根据依赖关系自动添加

SET(CMAKE_PREFIX_PATH  "/usr/local/Cellar/qt/5.15.0/")
#find_package(Qt5Widgets)
find_package(Qt5Core)
#find_package(Qt5Gui)


# add_library(token token.hpp)
# target_link_libraries(stone PUBLIC Token)


# add the executable
# 添加一个可执行文件
add_executable(stone stone.cpp
  object/hiObject.cpp
  runtime/universe.cpp
  object/hiString.cpp
  )

# add the binary tree to the search path for include files
# so that we will find TutorialConfig.h
# 将二进制目录添加到包含文件的搜索路径中，以便我们找到TutorialConfig.h
target_include_directories(stone PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

#添加Qt5依赖项
#target_link_libraries(${PROJECT_NAME} Qt5::Widgets Qt5::Core Qt5::Gui)
target_link_libraries(${PROJECT_NAME} Qt5::Core)


enable_testing()
ADD_TEST(NAME test_var COMMAND ./stone ../test/var.pyc)
SET_TESTS_PROPERTIES(test_var PROPERTIES PASS_REGULAR_EXPRESSION "1\n2\n3\n4\n5\n6\n7\n")

ADD_TEST(NAME test_if COMMAND ./stone ../test/if.pyc)
SET_TESTS_PROPERTIES(test_if PROPERTIES PASS_REGULAR_EXPRESSION "2\n3\n")

ADD_TEST(NAME test_for COMMAND ./stone ../test/for.pyc)
SET_TESTS_PROPERTIES(test_for PROPERTIES PASS_REGULAR_EXPRESSION "1\n1\n2\n3\n5\n8\n13\n21\n34\n55\n")

ADD_TEST(NAME test_break COMMAND ./stone ../test/break.pyc)
SET_TESTS_PROPERTIES(test_break PROPERTIES PASS_REGULAR_EXPRESSION "0\n1\n2\n1\n0\n1\n2\n2\n0\n1\n2\n")

ADD_TEST(NAME test_hello COMMAND ./stone ../test/hello.pyc)
SET_TESTS_PROPERTIES(test_hello PROPERTIES PASS_REGULAR_EXPRESSION "9\n")







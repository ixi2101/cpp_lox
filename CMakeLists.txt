cmake_minimum_required(VERSION 3.28)
project(cpplox)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_library(liblox src/Lox.cpp src/Scanner.cpp src/Token.cpp)
target_include_directories(liblox PUBLIC include)

add_executable(lox main.cpp)

target_compile_options(lox PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_include_directories(lox PRIVATE extern/lyra/include)
target_link_libraries(lox liblox)

cmake_minimum_required(VERSION 3.28)
project(cpplox)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_Declare(
  lyra
  GIT_REPOSITORY https://github.com/bfgroup/Lyra.git
  GIT_TAG a8bb6e22ea4dcd507292ecdb6443bad23ef7bfeb
)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(lyra)

add_library(liblox src/Lox.cpp src/Scanner.cpp src/Token.cpp)
target_include_directories(liblox PUBLIC include)

add_executable(lox main.cpp)

target_compile_options(lox PRIVATE -Wall -Wextra -Wpedantic -Werror)
target_link_libraries(lox liblox bfg::lyra)

add_subdirectory(test)

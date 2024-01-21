enable_testing()

add_executable(lox_test lox_test.cpp)
target_include_directories(lox_test PUBLIC lox)
target_link_libraries(lox_test GTest::gtest_main liblox)

include(GoogleTest)
gtest_discover_tests(lox_test)
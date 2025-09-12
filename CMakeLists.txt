cmake_minimum_required(VERSION 3.20)
project(RPN_Calculator)

set(CMAKE_CXX_STANDARD 17)

# Главная программа
add_executable(rpn_calculator src/main.cpp src/rpn.cpp)

# Тесты (если есть папка tests)
if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_rpn.cpp)
    enable_testing()
    add_executable(rpn_tests tests/test_rpn.cpp src/rpn.cpp)
    target_link_libraries(rpn_tests PRIVATE gtest_main)
    target_include_directories(rpn_calculator PRIVATE ${CMAKE_SOURCE_DIR}/include)
endif()

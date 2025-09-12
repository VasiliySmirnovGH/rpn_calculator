cmake_minimum_required(VERSION 3.14)
project(RPN_Calculator)

# Автоматически загружаем Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9fd718599d30c5a4435c5c8.zip
)
FetchContent_MakeAvailable(googletest)

# Ваш основной target
add_executable(rpn_calculator src/main.cpp src/rpn.cpp)
target_include_directories(rpn_calculator PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Тесты
add_executable(rpn_tests tests/test_rpn.cpp)
target_include_directories(rpn_tests PRIVATE ${CMAKE_SOURCE_DIR}/include)
target_include_directories(rpn_tests PRIVATE)
    ${CMAKE_SOURCE_DIR}/include
    /usr/include/gtest

# Линкуем с gtest
target_link_libraries(rpn_tests PRIVATE gtest_main)

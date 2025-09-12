# Находим GoogleTest
find_package(GTest REQUIRED)

# Тестовый исполняемый файл
add_executable(rpn_tests test_rpn.cpp)

# Линкуем с основным проектом и GTest
target_link_libraries(rpn_tests PRIVATE rpn_calculator GTest::GTest GTest::Main)

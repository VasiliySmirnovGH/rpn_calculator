# Главный исполняемый файл
add_executable(rpn_calculator main.cpp rpn.cpp)

# Установка целевого файла
install(TARGETS rpn_calculator DESTINATION bin)

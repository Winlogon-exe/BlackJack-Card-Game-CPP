cmake_minimum_required(VERSION 3.10) 
project(Black_Jack)                    

# Устанавливаем стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Добавляем директорию с заголовочными файлами
include_directories(inc)

# Указываем исходные файлы для компиляции
file(GLOB SOURCES "src/*.cpp")

# Создаем исполняемый файл из исходных файлов
add_executable(Black_Jack ${SOURCES})
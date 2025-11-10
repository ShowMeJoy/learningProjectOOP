cmake_minimum_required(VERSION 3.10)

project(MyHomeworkProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Опция для генерации compile_commands.json
# cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -S . -B build
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(main_exec main.cpp)


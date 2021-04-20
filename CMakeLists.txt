cmake_minimum_required(VERSION 3.11)
project(3d-world)
add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp model.cpp camera.cpp)
enable_abcg(${PROJECT_NAME})

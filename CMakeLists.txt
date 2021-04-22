cmake_minimum_required(VERSION 3.11)
project(3d-world)
add_executable(${PROJECT_NAME} main.cpp openglwindow.cpp model.cpp camera.cpp eventhandler.cpp map.cpp groundblock.cpp sea.cpp)
enable_abcg(${PROJECT_NAME})


cmake_minimum_required(VERSION 3.10.0 FATAL_ERROR)

project(HelloWorld LANGUAGES CXX)

set(project_sources main.cpp)

add_executable(${PROJECT_NAME} ${project_sources})

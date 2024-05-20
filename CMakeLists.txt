cmake_minimum_required(VERSION 3.26)
project(Test_task_YADRO)

set(CMAKE_CXX_STANDARD 20)

add_executable(Test_task_YADRO main.cpp
        input_validator.cpp
        input_validator.h
        entities.h
        computer_club.cpp
        computer_club.h
)
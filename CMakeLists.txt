# cmake_minimum_required(VERSION <specify CMake version here>)
project(Serial_Keyboard_Server_GUI)

set(CMAKE_CXX_STANDARD 11)

add_executable(Serial_Keyboard_Server_GUI
        console.cpp
        console.h
        ledindicator.cpp
        ledindicator.h
        main.cpp
        mainwindow.cpp
        mainwindow.h)

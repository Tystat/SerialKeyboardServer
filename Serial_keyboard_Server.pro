QT += core
QT -= gui
QT += serialport

CONFIG += c++11

TARGET = Serial_keyboard_Server
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    serialreader.cpp

HEADERS += \
    serialreader.h

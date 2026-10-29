QT += core gui widgets serialport testlib
CONFIG += c++11 testcase
TARGET = serial_port_tests
SOURCES += tst_widget.cpp ../widget.cpp
HEADERS += ../widget.h
FORMS += ../widget.ui
INCLUDEPATH += ..

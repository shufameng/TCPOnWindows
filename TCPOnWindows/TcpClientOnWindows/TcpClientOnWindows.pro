#-------------------------------------------------
#
# Project created by QtCreator 2017-07-13T16:50:26
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpClientOnWindows
TEMPLATE = app

LIBS += -lws2_32

SOURCES += main.cpp\
        tcpclientwindow.cpp

HEADERS  += tcpclientwindow.h

FORMS    += tcpclientwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2017-07-13T16:49:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TcpServerOnWindows
TEMPLATE = app

LIBS += -lws2_32

SOURCES += main.cpp\
        tcpserverwindow.cpp \
    tcpserver.cpp \
    basethread.cpp \
    recvthread.cpp \
    acceptthread.cpp

HEADERS  += tcpserverwindow.h \
    tcpserver.h \
    basethread.h \
    recvthread.h \
    acceptthread.h

FORMS    += tcpserverwindow.ui

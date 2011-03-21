QT       += core gui

TARGET = ResourceFileHelper

TEMPLATE = app

win32:RC_FILE = ResourceFileHelper.rc

DEFINES += VERSION="1.0"

SOURCES += \
    MainWindow.cpp \
    ReadWidget.cpp \
    WriteWidget.cpp \
    main.cpp \
    AboutWidget.cpp \
    ResourceFile.cpp \
    TableModel.cpp \
    TableView.cpp

HEADERS += \
    MainWindow.h \
    ReadWidget.h \
    WriteWidget.h \
    AboutWidget.h \
    ResourceFile.h \
    order32.h \
    TableModel.h \
    TableView.h

#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T15:41:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LeagueAssistant
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG+= static

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

LIBS += D:/curl-7.40.0-devel-mingw64/lib64/libcurl.a

LIBS += D:/curl-7.40.0-devel-mingw64/lib64/libcurldll.a

INCLUDEPATH += D:/curl-7.40.0-devel-mingw64/include

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    jsonfmcpp/nlohmann_json.hpp \
    datagather.h \
    champion.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2016-08-25T16:07:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = LargeWindow
TEMPLATE = app

TRANSLATIONS = LargeWindow_ru.ts

SOURCES += main.cpp\
           myApplication.cpp \
           my_MainWindow.cpp \
           my_dialogframe.cpp \
           other.cpp \
           subwindows.cpp \
           non_modal_dialog.cpp \
           data.cpp \
           auto_frame.cpp \
           auto_dialog.cpp \
           plus_dialog.cpp \
           systemtray.cpp \
           drawimage.cpp \
           file_system.cpp \
           table_multiplication.cpp


HEADERS  += \
           myApplication.h \
           my_MainWindow.h \
           my_dialogframe.h \
           other.h \
           subwindows.h \
           non_modal_dialog.h \
           data.h \
           auto_frame.h \
           auto_dialog.h \
           plus_dialog.h \
           systemtray.h \
           drawimage.h \
           file_system.h \
           table_multiplication.h


FORMS    +=


RESOURCES += \
    sources.qrc

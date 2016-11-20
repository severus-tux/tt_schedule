#-------------------------------------------------
#
# Project created by QtCreator 2016-11-17T13:06:15
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tt_schedule
TEMPLATE = app


SOURCES += main.cpp\
        tt_main_window.cpp \
    choose_view.cpp \
    input.cpp \
    tt_database.cpp \
    tt_table_view.cpp \
    schedule.cpp

HEADERS  += tt_main_window.h \
    choose_view.h \
    input.h \
    tt_database.h \
    tt_table_view.h \
    schedule.h

FORMS    += tt_main_window.ui \
    choose_view.ui \
    input.ui \
    tt_table_view.ui

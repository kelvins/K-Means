#-------------------------------------------------
#
# Project created by QtCreator 2015-10-26T09:28:10
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = KMEANS
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    kmeans.cpp \
    qcustomplot.cpp

HEADERS  += mainwindow.h \
    kmeans.h \
    qcustomplot.h

FORMS    += mainwindow.ui

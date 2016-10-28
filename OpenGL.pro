#-------------------------------------------------
#
# Project created by QtCreator 2016-09-28T16:25:03
#
#-------------------------------------------------

QT += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TARGET = OpenGL
TEMPLATE = app

LIBS += -lopengl32

SOURCES += main.cpp\
           mainwindow.cpp \
           openglwidget.cpp

HEADERS += mainwindow.h \
           openglwidget.h

FORMS += mainwindow.ui

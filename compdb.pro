QT		+= core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = compdb
TEMPLATE = app

SOURCES += main.cpp\
        mainwindow.cpp \
		dialog_category.cpp \
		dialog_type.cpp \
		dialog_footprint.cpp \

HEADERS	+= mainwindow.h \
		dialog_category.h \
		dialog_type.h \
		dialog_footprint.h \

FORMS	+= mainwindow.ui \
		dialog_category.ui \
		dialog_type.ui \
		dialog_footprint.ui \

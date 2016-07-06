QT		+= core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = compdb
TEMPLATE = app

SOURCES += main.cpp\
        main_window.cpp \
		dialog_category.cpp \
		dialog_type.cpp \
		dialog_footprint.cpp \
		dialog_temp.cpp \
		dialog_component.cpp

HEADERS	+= main_window.h \
		dialog_category.h \
		dialog_type.h \
		dialog_footprint.h \
		dialog_temp.h \
		dialog_component.h

FORMS	+= main_window.ui \
		dialog_category.ui \
		dialog_type.ui \
		dialog_footprint.ui \
		dialog_temp.ui \
		dialog_component.ui

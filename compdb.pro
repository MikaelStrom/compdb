QT			+= core gui widgets sql

TEMPLATE	= app
TARGET		= compdb
ICON		= chip.icns
RC_FILE		= compdb.rc
QMAKE_INFO_PLIST = Info.plist

SOURCES += main.cpp\
        main_window.cpp \
        sort_proxy.cpp \
        rel_delegate.cpp \
		dialog_category.cpp \
		dialog_type.cpp \
		dialog_footprint.cpp \
		dialog_temp.cpp \
		dialog_suppl.cpp \
		dialog_component.cpp

HEADERS	+= main_window.h \
        sort_proxy.h \
        rel_delegate.h \
		dialog_category.h \
		dialog_type.h \
		dialog_footprint.h \
		dialog_temp.h \
		dialog_suppl.h \
		dialog_component.h

FORMS	+= main_window.ui \
		dialog_category.ui \
		dialog_type.ui \
		dialog_footprint.ui \
		dialog_temp.ui \
		dialog_suppl.ui \
		dialog_component.ui

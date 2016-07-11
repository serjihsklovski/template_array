TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CFLAGS += -std=c11

SOURCES += main.c \
    lib/cexception/CException.c \
    test/arrray_double.c

DISTFILES += \
    lib/cexception/LICENSE.txt \
    .gitignore

HEADERS += \
    lib/cclasses/cclasses.h \
    lib/cexception/CException.h \
    template_array.h \
    test/arrray_double.h \
    error_codes.h

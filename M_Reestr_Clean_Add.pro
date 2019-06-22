#-------------------------------------------------
#
# Project created by QtCreator 2019-03-28T09:55:32
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = M_Reestr_Clean_Add
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    my_page.cpp \
    reestr_page.cpp \
    disp_page.cpp

HEADERS  += mainwindow.h \
    my_page.h \
    global.h \
    reestr_page.h \
    disp_page.h

FORMS    +=

win32
{
 RC_FILE = myapp.rc
 CONFIG -= embed_manifest_exe
}

DISTFILES += \
    myapp.rc \
    manifest.xml

RESOURCES += \
    rec.qrc



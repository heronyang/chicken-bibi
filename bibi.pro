QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bibi
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

RESOURCES += \
    application.qrc

DISTFILES += \
    res/background.gif \
    res/buttonEat.png \
    res/buttonHeal.png \
    res/buttonShower.png \
    res/buttonTurnOffLight.png \
    res/buttonPlay.png

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
        res/background.png \
        res/buttonEat.png \
        res/buttonHeal.png \
        res/buttonPlay.png \
        res/buttonShower.png \
        res/buttonTurnOffLight.png \
        res/stateBorn.gif \
        res/stateHappy.gif \
        res/stateHungry.gif \
        res/stateNormal.gif \
        res/stateSick.gif \
        res/stateSleep.gif \
        res/stateDirty.gif \
        res/stateWalk.gif \
        res/stateWalkBackward.gif \
        res/lightOffScene.gif \
        res/fullness-0.png \
        res/fullness-1.png \
        res/fullness-2.png \
        res/fullness-3.png \
        res/fullness-4.png \
        res/fullness-5.png \
        res/fullness.png \ \
        res/happiness-0.png \
        res/happiness-1.png \
        res/happiness-2.png \
        res/happiness-3.png \
        res/happiness-4.png \
        res/happiness-5.png \
        res/happiness.png \
        res/icon.icns

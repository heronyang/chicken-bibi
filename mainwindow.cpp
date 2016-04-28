#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QApplication>
#include <QDateTime>
#include <QIcon>

#include <string>
#include <ctime>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupUiComponents();

}

void MainWindow::setupUiComponents() {
    setupStaticBackground();
    setupStatus();
    setupButtons();
    setupBibi();
    setupHourClock();
}

void MainWindow::setupStaticBackground() {

    QPixmap background(":/background");
    QRegion exposed;
    QPalette palette;

    background.scroll(-backgroundImageOffset, 0, background.rect(), &exposed);
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

}

void MainWindow::setupAnimatedBackground() {
    backgroundAnimationTimerId = startTimer(20);
}

void MainWindow::setupStatus() {
    drawStaticImageAt(":/fullness", -10, -10, 135, 135);
    drawStaticImageAt(":/happiness", 290, -10, 135, 135);
    setFullnessTo(3);
    setHappinessTo(3);
}

void MainWindow::drawStaticImageAt(std::string resName, int x, int y, int w, int h) {
    QLabel *topLevelLabel = new QLabel(this);
    QPixmap pixmap(QString::fromStdString(resName));
    topLevelLabel->setPixmap(pixmap);
    topLevelLabel->setGeometry(x, y, w, h);
    topLevelLabel->show();
}

void MainWindow::setFullnessToFull() {
    fullness = 5;
    syncFullness();
}

void MainWindow::increaseFullness() {

    if(fullness < 5) {
        fullness ++;
    }
    syncFullness();

}

void MainWindow::decreaseFullness() {

    if(fullness > 0) {
        fullness --;
    }
    syncFullness();

    if(fullness == 0) {
        addAndDisplayNewState(hungry);
    }

}

void MainWindow::syncFullness() {
    setFullnessTo(fullness);
}

void MainWindow::setHappinessToFull() {
    happiness = 5;
    syncHappiness();
}

void MainWindow::increaseHappiness() {
    if(happiness < 5) {
        happiness ++;
    }
    syncHappiness();
}

void MainWindow::decreaseHappiness() {
    if(happiness > 0) {
        happiness --;
    }
    syncHappiness();
}

void MainWindow::syncHappiness() {
    setHappinessTo(happiness);
}


void MainWindow::setFullnessTo(int val) {
    fullness = val;
    if(fullnessBar == NULL) {
        fullnessBar = new QLabel(this);
        fullnessBar->setGeometry(100, 38, 160, 36);
    }
    std::string resName = ":/fullness" + std::to_string (val);
    QPixmap pixmap(QString::fromStdString(resName));
    fullnessBar->setPixmap(pixmap);
    fullnessBar->show();
}


void MainWindow::setHappinessTo(int val) {
    happiness = val;
    if(happinessBar == NULL) {
        happinessBar = new QLabel(this);
        happinessBar->setGeometry(400, 38, 160, 36);
    }
    std::string resName = ":/happiness" + std::to_string (val);
    QPixmap pixmap(QString::fromStdString(resName));
    happinessBar->setPixmap(pixmap);
    happinessBar->show();
}

void MainWindow::setupBibi() {
    born();
}

void MainWindow::setupHourClock() {
    QTimer *clock = new QTimer(this);
    connect(clock, SIGNAL(timeout()), this, SLOT(hourClockTickHandler()));
    clock->start(1000 * 60 * 60); // hourly
}

void MainWindow::born() {
    isInAction = true;
    changeBibiAnimationTo(":/stateBorn");
    QTimer *timer = new QTimer(this);
    timer->singleShot(7000, this, SLOT(nullFinishHandler()));
}

void MainWindow::happyWithFinishHandler(HandlerType handlerType) {

    isInAction = true;

    stopBackgroundAnimation();
    changeBibiAnimationTo(":/stateHappy");

    QTimer *timer = new QTimer(this);
    switch(handlerType) {
        case nothing:
            timer->singleShot(5000, this, SLOT(nullFinishHandler()));
            break;
        case killCurrentNeed:
            timer->singleShot(5000, this, SLOT(killCurrentNeedFinishHandler()));
            break;
    }

}

void MainWindow::nullFinishHandler() {
    isInAction = false;
    changeBibiToState(normal);
}

void MainWindow::killCurrentNeedFinishHandler() {

    isInAction = false;

    if(stateStack.isEmpty()) {
        changeBibiToState(normal);
        return;
    }

    stateStack.pop();
    if(stateStack.isEmpty()) {
        qDebug("is empty, and switching to normal");
        changeBibiToState(normal);
    } else {
        qDebug("is not empty");
        changeBibiToState(stateStack.top());
    }

}

void MainWindow::changeBibiToState(State state) {

    switch (state) {
    case normal:
        standInNormalStateForced();
        break;
    case hungry:
        changeBibiAnimationTo(":/stateHungry");
        break;
    case sick:
        changeBibiAnimationTo(":/stateSick");
        break;
    case sleepy:
        changeBibiAnimationTo(":/stateSleep");
        break;
    case dirty:
        changeBibiAnimationTo(":/stateDirty");
        break;

    }

}

void MainWindow::walkInNormalState() {
    if(!stateStack.isEmpty() || isInAction || lastNormalStateAction == walk) {
        qDebug("walk handle is ignored");
        return;
    }
    setupAnimatedBackground();
    if(backgroundImageFaceRight) {
        changeBibiAnimationTo(":/stateWalk");
    } else {
        changeBibiAnimationTo(":/stateWalkBackward");
    }
    lastNormalStateAction = walk;
    randomChangeToStand();
}

void MainWindow::randomChangeToStand() {

    srand(time(0));
    int randomTime = ((rand() % 20) + 5) * 1000; // 20~40 seconds
    qDebug("random change to stand time: %d", randomTime);

    QTimer *timer = new QTimer(this);
    timer->singleShot(randomTime, this, SLOT(standInNormalState()));

}

void MainWindow::standInNormalState() {
    if(lastNormalStateAction == stand) {
        return;
    }
}

void MainWindow::standInNormalStateForced() {

    qDebug("in normal state stand");

    stopBackgroundAnimation();

    if(!stateStack.isEmpty() || isInAction) {
        qDebug("stand handle is ignored");
        return;
    }
    changeBibiAnimationTo(":/stateNormal");
    lastNormalStateAction = stand;
    randomChangeToWalk();

}

void MainWindow::randomChangeToWalk() {

    srand(time(0));
    int randomTime = ((rand() % 20) + 5) * 1000; // 20~40 second
    qDebug("random change to walk time: %d", randomTime);

    QTimer *timer = new QTimer(this);
    timer->singleShot(randomTime, this, SLOT(walkInNormalState()));

}


void MainWindow::addAndDisplayNewState(State newState) {
    if(!stateStack.isEmpty() && newState == stateStack.top()) {
        return;
    }
    stopBackgroundAnimation();
    stateStack.push(newState);
    changeBibiToState(newState);
}

void MainWindow::stopBackgroundAnimation() {
    if(backgroundAnimationTimerId) {
        killTimer(backgroundAnimationTimerId);
        backgroundAnimationTimerId = 0;
    }
}

void MainWindow::changeBibiAnimationTo(std::string resName) {

    removePreviousAnimationIfExists();

    QMovie *bibi = new QMovie(QString::fromStdString(resName));
    if (!bibi->isValid()) {
        qDebug("bibi animation is not found");
    }

    bibiContainer = new QLabel(this);
    bibiContainer->setMovie(bibi);
    bibiContainer->setGeometry(150, 130, 300, 390);
    bibiContainer->show();
    bibi->start();

}

void MainWindow::removePreviousAnimationIfExists() {
    if (bibiContainer != NULL) {
        bibiContainer->deleteLater();
        bibiContainer = NULL;
    }
}

void MainWindow::hourClockTickHandler() {
    QDateTime now = QDateTime::currentDateTime();
    int hour = now.toString("H").toInt();
    qDebug("%d", hour);
    hourlyWorkAssignment(hour);
}

void MainWindow::hourlyWorkAssignment(int hour) {

    if(hour % 2 == 0) {
        decreaseFullness();
    }

    if(hour % 3 == 0) {
        decreaseHappiness();
    }

    if(hour == 19) {    // 7pm
        addAndDisplayNewState(dirty);
    }

    if(hour >= 22 || hour <= 7) {
        if(stateStack.isEmpty() || stateStack.top() != sleepy) {
            addAndDisplayNewState(sleepy);
        }
    }

    if(hour >= 8 && hour <= 21) {
        if(!isLightOn()) {
            morningArrived();
        }
    }

    if(randomYesInEvery(72)) {
        addAndDisplayNewState(sick);
    }

}

bool MainWindow::randomYesInEvery(int val) {
    srand(time(0));
    return (rand() % val) == 0; // 20~40 seconds
}

void MainWindow::setupButtons() {
    connect(ui->buttonEat, SIGNAL(clicked()), this , SLOT(buttonEatHandler()));
    connect(ui->buttonShower, SIGNAL(clicked()), this , SLOT(buttonShowerHandler()));
    connect(ui->buttonHeal, SIGNAL(clicked()), this , SLOT(buttonHealHandler()));
    connect(ui->buttonPlay, SIGNAL(clicked()), this , SLOT(buttonPlayHandler()));
    connect(ui->buttonTurnOffLight, SIGNAL(clicked()), this , SLOT(buttonTurnOffLightHandler()));
}

void MainWindow::buttonEatHandler() {
    qDebug("eat button clicked");
    if(isInAction) {
        qDebug("in action, blocked");
        return;
    }
    if(stateStack.isEmpty()) {
        increaseFullness();
        happyWithFinishHandler(nothing);
    } else if (stateStack.top() == hungry) {
        increaseFullness();
        happyWithFinishHandler(killCurrentNeed);
    }
}

void MainWindow::buttonShowerHandler() {
    qDebug("shower button clicked");
    if(isInAction) {
        qDebug("in action, blocked");
        return;
    }
    if(!stateStack.isEmpty() && stateStack.top() == dirty) {
        increaseHappiness();
        happyWithFinishHandler(killCurrentNeed);
    }
}

void MainWindow::buttonHealHandler() {
    qDebug("heal button clicked");
    if(isInAction) {
        qDebug("in action, blocked");
        return;
    }
    if(!stateStack.isEmpty() && stateStack.top() == heal) {
        setHappinessToFull();
        happyWithFinishHandler(killCurrentNeed);
    }
}

void MainWindow::buttonPlayHandler() {
    qDebug("play button clicked");
    if(isInAction) {
        qDebug("in action, blocked");
        return;
    }
    if(!stateStack.isEmpty()) {
        return;
    }
    increaseHappiness();
    happyWithFinishHandler(nothing);
}

void MainWindow::buttonTurnOffLightHandler() {
    qDebug("turn off light button clicked");
    if(isInAction) {
        qDebug("in action, blocked");
        return;
    }
    if(!stateStack.isEmpty() && stateStack.top() == sleepy) {
        turnOffLight();
    }
}

void MainWindow::turnOffLight() {
    QMovie *lightOffScene = new QMovie(QString::fromStdString(":/lightOffScene"));
    if (!lightOffScene->isValid()) {
        qDebug("lightOffScene animation is not found");
    }

    lightOffContainer = new QLabel(this);
    lightOffContainer->setMovie(lightOffScene);
    lightOffContainer->setGeometry(0, 0, 600, 600);
    lightOffContainer->show();
    lightOffScene->start();
}

void MainWindow::turnOnLight() {
    if(lightOffContainer != NULL) {
        lightOffContainer->deleteLater();
        lightOffContainer = NULL;
    }
}

bool MainWindow::isLightOn() {
    return lightOffContainer == NULL;
}

void MainWindow::morningArrived() {
    turnOnLight();
    happyWithFinishHandler(killCurrentNeed);
}

MainWindow::~MainWindow() {
    killTimer(backgroundAnimationTimerId);
    delete ui;
}

void MainWindow::timerEvent(QTimerEvent *event) {

    QPixmap background(":/background");
    QRegion exposed;
    QPalette palette;

    background.scroll(-backgroundImageOffset, 0, background.rect(), &exposed);
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    int delta = 1;
    if (backgroundImageFaceRight) {
        backgroundImageOffset += delta;
    } else {
        backgroundImageOffset -= delta;
    }

    checkAndTurnBackgroundImageFacing();

}

void MainWindow::checkAndTurnBackgroundImageFacing() {
    if (backgroundImageOffset >= 1800 - 600) {
        backgroundImageFaceRight = false;
        if(!isInAction && stateStack.isEmpty()) {
            changeBibiAnimationTo(":/stateWalkBackward");
        }
    } else if (backgroundImageOffset <= 0) {
        backgroundImageFaceRight = true;
        if(!isInAction && stateStack.isEmpty()) {
            changeBibiAnimationTo(":/stateWalk");
        }
    }
}

void MainWindow::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

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
    setFullnessTo(5);
    setHappinessTo(5);
}

void MainWindow::drawStaticImageAt(std::string resName, int x, int y, int w, int h) {
    QLabel *topLevelLabel = new QLabel(this);
    QPixmap pixmap(QString::fromStdString(resName));
    topLevelLabel->setPixmap(pixmap);
    topLevelLabel->setGeometry(x, y, w, h);
    topLevelLabel->show();
}

void MainWindow::setFullnessTo(int val) {
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
    changeBibiToAction(born, 7000);
}

void MainWindow::setupHourClock() {
    QTimer *clock = new QTimer(this);
    connect(clock, SIGNAL(timeout()), this, SLOT(hourClockTickHandler()));
    clock->start(1000 * 60 * 60); // hourly
}


void MainWindow::changeBibiToAction(Action action, int duration) {

    currentState = inAction;

    switch (action) {
    case born:
        changeBibiAnimationTo(":/stateBorn");
        break;
    case happy:
        changeBibiAnimationTo(":/stateHappy");
        break;
    }

    QTimer *timer = new QTimer(this);
    timer->singleShot(duration, this, SLOT(actionFinishHandler()));

}

void MainWindow::actionFinishHandler() {
    changeBibiToState(normal);
}

void MainWindow::changeBibiToState(State state) {

    currentState = state;

    switch (state) {
    case normal:
        standInNormalState();
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
        // TODO: wait for the gif file
        break;

    }

}

void MainWindow::walkInNormalState() {
    if(currentState != normal) {
        return;
    }
    setupAnimatedBackground();
    if(backgroundImageFaceRight) {
        changeBibiAnimationTo(":/stateWalk");
    } else {
        changeBibiAnimationTo(":/stateWalkBackward");
    }
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

    killTimer(backgroundAnimationTimerId);

    qDebug("in normal state stand");
    if(currentState != normal) {
        return;
    }
    changeBibiAnimationTo(":/stateNormal");
    randomChangeToWalk();
}

void MainWindow::randomChangeToWalk() {

    srand(time(0));
    int randomTime = ((rand() % 20) + 5) * 1000; // 20~40 second
    qDebug("random change to walk time: %d", randomTime);

    QTimer *timer = new QTimer(this);
    timer->singleShot(randomTime, this, SLOT(walkInNormalState()));

}


void MainWindow::becomeHungry() {
    changeBibiToState(hungry);
}

void MainWindow::becomeSick() {
    changeBibiToState(sick);
}

void MainWindow::becomeSleepy() {
    changeBibiToState(sleepy);
}

void MainWindow::becomeDirty() {
    changeBibiToState(dirty);
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
    qDebug("%s", qPrintable(now.toString()));
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
    // TODO: eating animation here
    changeBibiToAction(happy, 5000);
}

void MainWindow::buttonShowerHandler() {
    qDebug("shower button clicked");
    QTimer *timer = new QTimer(this);
    timer->singleShot(1000, this, SLOT(becomeSleepy()));
    if(currentState != dirty) {
        return;
    }
    changeBibiToAction(happy, 5000);
}

void MainWindow::buttonHealHandler() {
    qDebug("heal button clicked");
    changeBibiToAction(happy, 5000);
}

void MainWindow::buttonPlayHandler() {
    qDebug("play button clicked");
    changeBibiToAction(happy, 5000);
}

void MainWindow::buttonTurnOffLightHandler() {
    qDebug("turn off light button clicked");
    turnOffLight();
    QTimer *timer = new QTimer(this);
    timer->singleShot(3000, this, SLOT(morningArrived()));
    if(currentState != sleepy) {
        return;
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

void MainWindow::morningArrived() {
    turnOnLight();
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
        if(currentState == normal) {
            changeBibiAnimationTo(":/stateWalkBackward");
        }
    } else if (backgroundImageOffset <= 0) {
        backgroundImageFaceRight = true;
        if(currentState == normal) {
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>
#include <QLabel>
#include <QPushButton>
#include <QTime>
#include <QTimer>
#include <QThread>
#include <QApplication>

#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupUiComponents();

}

void MainWindow::setupUiComponents() {
    setupStaticBackground();
    setupButtons();
    setupBibi();
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

void MainWindow::setupBibi() {
    changeBibiToAction(born);
}

void MainWindow::changeBibiToAction(Action action) {

    changeBibiAnimationTo(":/stateBorn");

    QTimer *timer = new QTimer(this);
    timer->singleShot(6000, this, SLOT(actionFinishHandler()));

}

void MainWindow::actionFinishHandler() {
    changeBibiAnimationTo(":/stateNormal");
}

void MainWindow::changeBibiAnimationTo(std::string resName) {

    if (bibiContainer != NULL) {
        bibiContainer->deleteLater();
        bibiContainer = NULL;
    }

    QMovie *bibi = new QMovie(QString::fromStdString(resName));
    if (!bibi->isValid()) {
        qDebug("bibi animation is not found");
    } else {
        qDebug("bibi animation is set");
    }

    bibiContainer = new QLabel(this);
    bibiContainer->setMovie(bibi);
    bibiContainer->setGeometry(150, 130, 300, 390);
    bibiContainer->show();
    bibi->start();

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
    changeBibiAnimationTo(":/stateHappy");
}

void MainWindow::buttonShowerHandler() {
    qDebug("shower button clicked");
    changeBibiAnimationTo(":/stateHappy");
}

void MainWindow::buttonHealHandler() {
    qDebug("heal button clicked");
    changeBibiAnimationTo(":/stateHappy");
}

void MainWindow::buttonPlayHandler() {
    qDebug("play button clicked");
    changeBibiAnimationTo(":/stateHappy");
}

void MainWindow::buttonTurnOffLightHandler() {
    qDebug("turn off light button clicked");
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
    } else if (backgroundImageOffset <= 0) {
        backgroundImageFaceRight = true;
    }
}

void MainWindow::delay() {
    QTime dieTime= QTime::currentTime().addSecs(1);
    while (QTime::currentTime() < dieTime) {
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
    }
}

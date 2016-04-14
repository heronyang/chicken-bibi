#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>
#include <QLabel>
#include <QPushButton>
#include <QTime>

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
    changeBibiToAction(born, normal);
}

void MainWindow::changeBibiToAction(Action action, State finishState) {

    switch(action) {
    case Action::born :
        changeBibiAnimationTo(":/stateBorn");
        changeBibiAnimationTo(":/stateNormal");
        break;
    case Action::eat :
        break;
    case Action::heal :
        break;
    case Action::turnOffLight :
        break;
    case Action::shower :
        break;
    case Action::play :
        break;
    }

}

void MainWindow::changeBibiAnimationTo(std::string resName) {

    // TODO: remove previous bibi if exists (use class-life variable)

    QMovie *bibi = new QMovie(QString::fromStdString(resName));

    if (!bibi->isValid()) {
        qDebug("bibi animation is not found");
    } else {
        qDebug("bibi animation is set");
    }

    QLabel *bibiContainer = new QLabel(this);
    bibiContainer->setMovie(bibi);
    bibiContainer->setGeometry(150, 150, 300, 300);
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
}

void MainWindow::buttonShowerHandler() {
    qDebug("shower button clicked");
}

void MainWindow::buttonHealHandler() {
    qDebug("heal button clicked");
}

void MainWindow::buttonPlayHandler() {
    qDebug("play button clicked");
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

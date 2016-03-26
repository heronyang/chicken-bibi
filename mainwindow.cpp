#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>
#include <QLabel>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupUiComponents();

}

void MainWindow::setupUiComponents() {
    setupBackground();
    setupButtons();
}

void MainWindow::setupBackground() {

    QMovie *background = new QMovie(":/background");

    if (!background->isValid()) {
        qDebug("background animation is not found");
    } else {
        qDebug("background animation is set");
    }

    QLabel *backgroundContainer = new QLabel(this);
    backgroundContainer->lower();
    backgroundContainer->setMovie(background);
    backgroundContainer->setGeometry(0, 0, 600, 600);
    background->start();

}

void MainWindow::setupButtons() {
    QPixmap image(":/images/buttonPush");
    // buttonPush->setIcon(QIcon(image));
}

MainWindow::~MainWindow() {
    delete ui;
}

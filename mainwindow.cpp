#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMovie>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    setupUiComponents();

}

void MainWindow::setupUiComponents() {
    setupBackground();
}

void MainWindow::setupBackground() {
    QMovie *background = new QMovie(":/background");

    if (!background->isValid()) {
        qDebug("background animation is not found");
    } else {
        qDebug("background animation is set");
    }

    QLabel *backgroundContainer = new QLabel(this);
    backgroundContainer->setMovie(background);
    backgroundContainer->setGeometry(0, 0, 600, 600);
    background->start();
}

MainWindow::~MainWindow() {
    delete ui;
}

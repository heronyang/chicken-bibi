#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QPushButton;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    enum State {
        normal,
        walk,
        hungry,
        sick,
        sleep,
        dirty,
        lightOff
    };

    enum Action {
        born,
        eat,
        heal,
        turnOffLight,
        shower,
        play
    };

    void setupUiComponents();
    void setupStaticBackground();
    void setupAnimatedBackground();
    void setupButtons();
    void setupBibi();
    void changeBibiToAction(Action, State);
    void changeBibiAnimationTo(std::string);

    int backgroundAnimationTimerId;
    int backgroundImageOffset = 0;
    int backgroundImageFaceRight = true;
    void checkAndTurnBackgroundImageFacing();

    void delay();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void buttonEatHandler();
    void buttonShowerHandler();
    void buttonHealHandler();
    void buttonPlayHandler();
    void buttonTurnOffLightHandler();

};

#endif // MAINWINDOW_H

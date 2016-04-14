#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>

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
        sleepy,
        dirty,
        lightOff
    };

    enum Action {
        born,
        happy,
        eat,
        heal,
        shower,
        play
    };

    State currentState = normal;
    QLabel *bibiContainer = NULL;
    QLabel *lightOffContainer = NULL;

    void setupUiComponents();
    void setupStaticBackground();
    void setupAnimatedBackground();
    void setupButtons();
    void setupBibi();

    void changeBibiToAction(Action, int);
    void changeBibiToState(State);

    void changeBibiAnimationTo(std::string);
    void removePreviousAnimationIfExists();

    int backgroundAnimationTimerId;
    int backgroundImageOffset = 0;
    int backgroundImageFaceRight = true;
    void checkAndTurnBackgroundImageFacing();

    void turnOffLight();
    void turnOnLight();
    void delay();

protected:
    void timerEvent(QTimerEvent *event);

private slots:
    void buttonEatHandler();
    void buttonShowerHandler();
    void buttonHealHandler();
    void buttonPlayHandler();
    void buttonTurnOffLightHandler();

    void actionFinishHandler();
    void becomeHungry();
    void becomeSick();
    void becomeSleepy();
    void becomeDirty();

    void morningArrived();

};

#endif // MAINWINDOW_H

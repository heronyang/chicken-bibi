#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QStack>

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
        hungry,
        sick,
        sleepy,
        dirty,
        inAction
    };

    enum Action {
        happy,
        eat,
        heal,
        shower,
        play
    };

    enum HandlerType {
        nothing,
        killCurrentNeed
    };

    enum NormalStateAction {
        stand,
        walk,
        noAction
    };

    State currentState = normal;
    QLabel *bibiContainer = NULL;
    QLabel *lightOffContainer = NULL;
    QLabel *fullnessBar = NULL;
    QLabel *happinessBar = NULL;

    QStack<State> stateStack;

    int happiness = 5;
    int fullness = 5;

    bool isInAction = false;

    NormalStateAction lastNormalStateAction = noAction;

    void setupUiComponents();
    void setupStaticBackground();
    void setupAnimatedBackground();
    void setupStatus();
    void drawStaticImageAt(std::string, int, int, int, int);
    void setupButtons();
    void setupBibi();
    void setupHourClock();

    void born();
    void happyWithFinishHandler(HandlerType);

    void setFullnessToFull();
    void increaseFullness();
    void decreaseFullness();
    void syncFullness();

    void setHappinessToFull();
    void increaseHappiness();
    void decreaseHappiness();
    void syncHappiness();

    void setFullnessTo(int);
    void setHappinessTo(int);

    void changeBibiToState(State);

    void stopBackgroundAnimation();

    void changeBibiAnimationTo(std::string);
    void removePreviousAnimationIfExists();

    void randomChangeToStand();
    void randomChangeToWalk();

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

    void hourClockTickHandler();

    void buttonEatHandler();
    void buttonShowerHandler();
    void buttonHealHandler();
    void buttonPlayHandler();
    void buttonTurnOffLightHandler();

    void nullFinishHandler();
    void killCurrentNeedFinishHandler();
    void addAndDisplayNewState(State);

    void standInNormalState();
    void walkInNormalState();

    void morningArrived();

};

#endif // MAINWINDOW_H

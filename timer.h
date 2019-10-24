#ifndef TIMER_H
#define TIMER_H

#include <QMainWindow>
#include<QTimer>

namespace Ui {
class TimerScene;
}

class TimerScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit TimerScene(QWidget *parent = nullptr);
    ~TimerScene();

    double countTime=0.0;


signals:
    void chooseSceneBack();


private:
    Ui::TimerScene *ui;
};

#endif // TIMER_H

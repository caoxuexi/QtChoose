#ifndef CHOOSESCENE_H
#define CHOOSESCENE_H

#include <QMainWindow>
#include "lotteryscene.h"
#include "lottery.h"

class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);
    //LotteryScene *lotteryScene;
    Lottery *lottery;
signals:
    void chooseSceneBack();

public slots:
};

#endif // CHOOSESCENE_H

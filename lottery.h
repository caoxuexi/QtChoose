#ifndef LOTTERY_H
#define LOTTERY_H

#include <QMainWindow>
#include<timer.h>

namespace Ui {
class Lottery;
}

class Lottery : public QMainWindow
{
    Q_OBJECT

public:
    explicit Lottery(QWidget *parent = nullptr);
    ~Lottery();
    explicit Lottery(int index);
    int groupIndex;

    QString chooseList[16];

    int recordNum=0;

    TimerScene *timer=NULL;

    void LuanXu(QString a[], int length);//数组元素的乱序排列

    void delete_item(QString a[],QString item,int &recordNum);

signals:
    void chooseSceneBack();

private:
    Ui::Lottery *ui;
};

#endif // LOTTERY_H

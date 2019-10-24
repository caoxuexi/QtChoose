#ifndef LOTTERYSCENE_H
#define LOTTERYSCENE_H

#include <QMainWindow>


namespace Ui {
class LotteryScene;
}
class LotteryScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit LotteryScene(QWidget *parent = nullptr);
    LotteryScene(int index);
    ~LotteryScene();

    int groupIndex;
signals:
    void chooseSceneBack();
public slots:

private:
    Ui::LotteryScene *ui;
};

#endif // LOTTERYSCENE_H

#ifndef SETTINGINPUT_H
#define SETTINGINPUT_H

#include <QMainWindow>
#include<QString>
#include<mypushbutton.h>
#include<QLineEdit>
#include<QFile>
class SettingInput : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingInput(QWidget *parent = nullptr);

    SettingInput(int index);

    int groupIndex;

    QString theChooseName[16];

    MyPushButton *confirm;

    QLineEdit *editItem[16];

    QFile *fileInput;

signals:
    void chooseSceneBack();
    void chooseSceneStart();

public slots:
};

#endif // SETTINGINPUT_H

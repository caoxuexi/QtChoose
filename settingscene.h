#ifndef SETTINGSCENE_H
#define SETTINGSCENE_H

#include <QMainWindow>
#include<settinginput.h>
class SettingScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit SettingScene(QWidget *parent = nullptr);

    SettingInput *input=NULL;

signals:
    void chooseSceneBack();

public slots:
};

#endif // SETTINGSCENE_H

#ifndef STARTSCENE_H
#define STARTSCENE_H

#include <QMainWindow>
#include"choosescene.h"
#include"settingscene.h"
#include"settinginput.h"


namespace Ui {
class StartScene;
}

class StartScene : public QMainWindow
{
    Q_OBJECT

public:
    explicit StartScene(QWidget *parent = nullptr);
    ~StartScene();

    ChooseScene *chooseScene;

    SettingScene *settingScene;

//    SettingInput *settinginput;
private:
    Ui::StartScene *ui;
};

#endif // STARTSCENE_H

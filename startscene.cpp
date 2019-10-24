#include "startscene.h"
#include "ui_startscene.h"
//#include<QIcon>
#include<QLabel>
#include<QFont>
#include<QPushButton>
#include"settingscene.h"
#include"choosescene.h"
#include<QMessageBox>

StartScene::StartScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::StartScene)
{
    ui->setupUi(this);

    this->setFixedSize(400,300);
    this->setWindowTitle("小曹抽奖选择器");
    this->setWindowIcon(QIcon(":/res/Icon.png"));

    QLabel *title=new QLabel;
    title->setParent(this);
    QFont font;
    font.setFamily("情书翩翩体");
    font.setPointSize(25);
    title->setFont(font);
    QString str=QString("小曹选择器");
    title->setText(str);
    title->setScaledContents(true);
    title->setAlignment(Qt::AlignCenter);
    title->setGeometry(QRect((this->width()-250)*0.5,(this->height()-50)*0.5-25,250,50));

    this->chooseScene =new ChooseScene;
    this->settingScene= new SettingScene;
//    this->settinginput=new SettingInput(int a);
    connect(ui->actionSearch,&QAction::triggered,[=](){
        QMessageBox::about(this,"制作信息","Created by XiaoCao\nSpending one week\nCoding 1000 rows");
    });

    connect(ui->actionExit,&QAction::triggered,[=](){
        this->close();
    });

    connect(ui->Setting,&QPushButton::clicked,[=](){
        this->hide();
        this->settingScene->setGeometry(this->geometry());
        this->settingScene->show();
    });

    connect(ui->Enter,&QPushButton::clicked,[=](){
        this->hide();
        this->chooseScene->setGeometry(this->geometry());
        this->chooseScene->show();
    });

    //setting场景的切回信号
    connect(this->settingScene,&SettingScene::chooseSceneBack,[=](){
        this->setGeometry(this->settingScene->geometry());
        this->settingScene->hide();
        this->show();
    });

    //choose场景的切回信号
    connect(this->chooseScene,&ChooseScene::chooseSceneBack,[=](){
        this->setGeometry(this->chooseScene->geometry());
        this->chooseScene->hide();
        this->show();
    });

    //settinginput场景切回信号
//    connect(this->settinginput,&SettingInput::chooseSceneStart,[=](){
//        this->setGeometry(this->settinginput->geometry());
//        this->settinginput->hide();
//        this->show();
//    });
}

StartScene::~StartScene()
{
    delete ui;
}

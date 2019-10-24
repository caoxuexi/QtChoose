#include "lotteryscene.h"
#include "ui_lottery.h"
#include<QMenu>
#include<QMenuBar>
#include<QTimer>
#include "mypushbutton.h"
#include<QMessageBox>
LotteryScene::LotteryScene(QWidget *parent) : QMainWindow(parent)
{

}

LotteryScene::LotteryScene(int index) : ui(new Ui::LotteryScene)
{
    this->groupIndex=index;
    this->setFixedSize(600,600);
    this->setWindowTitle("随机界面");
    this->setWindowIcon(QIcon(":/res/Icon.png"));
    QMenuBar *bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("菜单");
    QAction *searchAction=startMenu->addAction("查看");
    connect(searchAction,&QAction::triggered,[=](){
        QMessageBox::about(this,"制作信息","Creat by XiaoCao\nSpending one week\nCoding 1000 rows");
    });
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮设置
    MyPushButton *backBtn= new MyPushButton(":/res/back.png");
    backBtn->setParent(this);
    backBtn->move((this->width()-backBtn->width())*0.5,this->height()-backBtn->height()-20);

    connect(backBtn,&MyPushButton::clicked,[=](){
        backBtn->Zoom1();
        backBtn->Zoom2();
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });
}

LotteryScene::~LotteryScene()
{
    delete ui;
}

#include "timer.h"
#include "ui_timer.h"
#include<QMessageBox>
#include<QTimer>
#include<QDebug>
#include<QSound>
TimerScene::TimerScene(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TimerScene)
{
    //设置音效
    QSound *inSound=new QSound(":/res/are~1.wav");
    inSound->setLoops(1);


    //设置一个计时器用于秒数的减少
    QTimer *timer=new QTimer();
    timer->setInterval(10);

    ui->setupUi(this);
    this->setFixedSize(800,600);
    //QString windowTitle=QString("第%1组随机抽取界面").arg(index);
    this->setWindowTitle("计时界面");
    this->setWindowIcon(QIcon(":/res/Icon.png"));
    QMenuBar *bar=this->menuBar();
    this->setMenuBar(bar);
    QMenu *startMenu=bar->addMenu("菜单");
    QAction *searchAction=startMenu->addAction("查看");
    connect(searchAction,&QAction::triggered,[=](){
        QMessageBox::about(this,"制作信息","Created by XiaoCao\nSpending one week\nCoding 1000 rows");
    });
    QAction *quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //lcdNumber的初始化
    ui->lcdNumber->setDigitCount(5);
    ui->lcdNumber->display("0.00");

    //返回按钮的封装
    connect(ui->backScene,&QPushButton::clicked,[=](){
        emit this->chooseSceneBack();
    });

    //开始停止按钮的封装
    connect(ui->stop,&QPushButton::clicked,[=](){


        if (ui->stop->text() == tr("开始"))
        {
             ui->stop->setText(tr("停止"));
             ui->stop->setIcon(QIcon(":/res/wrong2.png"));
             ui->stop->setIconSize(QSize(40,40));
             timer->start();

        }
        else if (ui->stop->text() == tr("停止"))
        {
          ui->stop->setText(tr("开始"));
          ui->stop->setIcon(QIcon(":/res/right3.png"));
          ui->stop->setIconSize(QSize(40,40));
          timer->stop();
//          bool active=timer->isActive();
//          qDebug()<<active;
        }

    });

    //定时器显示
    connect(timer,&QTimer::timeout,[=](){
        if(this->countTime<=0.00)
        {
            inSound->play();
            timer->stop();
            ui->lcdNumber->display("0.00");
            ui->stop->setText(tr("开始"));
            ui->stop->setIcon(QIcon(":/res/right3.png"));
            QMessageBox::information(this,"提示","Time out！");


        }
        else
        {
            this->countTime=this->countTime-0.01;
            if(this->countTime<0.0)
            {
                this->countTime=0.0;
            }
            char stopTime[32];
            sprintf(stopTime,"%.2lf",this->countTime);
            ui->lcdNumber->display(stopTime);

        }
    });

    //15s计时按钮的封装
    connect(ui->fifteens,&QPushButton::clicked,[=](){

//         QString tim="15.00";
//         QString timestr = tim.toString("mm:ss"); //设置时间格式
         ui->lcdNumber->display("15.00");
         this->countTime=15.0;
    });

    //20s计时按钮的封装
    connect(ui->twentys,&QPushButton::clicked,[=](){
         ui->lcdNumber->display("20.00");
         this->countTime=20.0;
    });

    //30s计时按钮的封装
    connect(ui->thirtys,&QPushButton::clicked,[=](){
         ui->lcdNumber->display("30.00");
         this->countTime=30.0;
    });

    //45s计时按钮的封装
    connect(ui->fortys,&QPushButton::clicked,[=](){
         ui->lcdNumber->display("45.00");
         this->countTime=45.0;
    });

    //60s计时按钮的封装
    connect(ui->sixtys,&QPushButton::clicked,[=](){
         ui->lcdNumber->display("60.00");
         this->countTime=60.0;
    });



}

TimerScene::~TimerScene()
{
    delete ui;
}

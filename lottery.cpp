#include "lottery.h"
#include "ui_lottery.h"
#include"mypushbutton.h"
#include<QMenu>
#include<QMenuBar>
#include<QMessageBox>
#include<QTimer>
#include<QString>
#include<QFile>
#include<QDir>
#include<QDebug>
#include<QTextCodec>
#include<QTime>
#include<QSound>

Lottery::Lottery(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Lottery)
{
    //ui->setupUi(this);
}

Lottery::Lottery(int index) :
    ui(new Ui::Lottery)
{
    //设置音效
    QSound *outSound=new QSound(":/res/magic.wav");
    outSound->setLoops(-1);

    qsrand(time(NULL));
    ui->setupUi(this);
    this->groupIndex=index;
    this->setFixedSize(800,600);
    QString windowTitle=QString("第%1组随机抽取界面").arg(index);
    this->setWindowTitle(windowTitle);
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

    //构建一个定时器，用于切换名字
    QTimer *timer=new QTimer(this);

    //新建一个列表用来存在还未抽到的人员名字(写在头文件里)

    //判断目录是否存在若不存在则创建
    QString openFile=QString("../QtChoose/file/%1.txt").arg(index);
    QString dir_str = "../QtChoose/file";
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
        qDebug() << "新建目录是否成功" << res;
    }

    this->chooseList->clear();

    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QFile file(openFile);
    file.setParent(this);
    file.open(QIODevice::ReadOnly);
    int line=0;
    if(!file.isOpen())
    {
        QMessageBox::critical(this,"打开错误","找不到所需要的文件,请检查有无填写配置文件！");
    }
    else
    {
        while(!file.atEnd())
        {
            this->chooseList[line]=file.readLine();
            line++;
            this->recordNum=line;
        }
        line=0;
        for(int i=0;chooseList[i]!="";i++)
        {
            qDebug()<<this->chooseList[i];
        }
    }

    //开始和停止按钮的设置
    connect(ui->btn_start,&QPushButton::clicked,[=](){

        if(this->chooseList->isEmpty())
        {
            QMessageBox::information(this,tr("提示对话框"),tr("已无人参加抽取，请点击重置按钮!"),QMessageBox::Ok);
                ui->btn_start->setEnabled(false);
                ui->name->clear();
        }



        else if (ui->btn_start->text() == tr("开始抽取")) {
            outSound->play();
            ui->btn_start->setText(tr("停止抽取"));
            ui->btn_start->setIcon(QIcon(":/res/wrong2.png"));
            ui->btn_start->setIconSize(QSize(50,50));
            timer->start(10);
            connect(timer,&QTimer::timeout,[=](){
                qsrand(QTime::currentTime().msec());
                int winner = (qrand()%this->recordNum);
                //ui->name->setAlignment(Qt::AlignBottom);
                ui->name->setText(this->chooseList[winner]);
            });
          }

          else if (ui->btn_start->text() == tr("停止抽取")) {
            outSound->stop();
            ui->btn_start->setText(tr("开始抽取"));
            ui->btn_start->setIcon(QIcon(":/res/right3.png"));
            ui->btn_start->setIconSize(QSize(50,50));
            QString over= ui->name->text();
            this->delete_item(this->chooseList,over,this->recordNum);
            timer->stop();
          }
    });

    //返回按钮的设置
    connect(ui->btn_back,&QPushButton::clicked,[=](){
        QTimer::singleShot(100,this,[=](){
             emit this->chooseSceneBack();
        });
    });

    //刷新按钮的设置
    connect(ui->btn_renew,&QPushButton::clicked,[=](){
        ui->btn_start->setEnabled(true);
        this->chooseList->clear();

        //QTextCodec *codec=QTextCodec::codecForName("UTF-8");
        QFile file(openFile);
        file.setParent(this);
        file.open(QIODevice::ReadOnly);
        int line=0;
        if(!file.isOpen())
        {
            QMessageBox::critical(this,"打开错误","找不到所需要的文件,请检查有无填写配置文件！");
        }
        else
        {
            while(!file.atEnd())
            {
                this->chooseList[line]=file.readLine();
                line++;
                this->recordNum=line;
            }
            line=0;
        }
        QMessageBox::information(this,"重置提示","重置成功，可以再次抽取！");
    });

    //计时页面按钮设置(进入)
    connect(ui->goTimer,&QPushButton::clicked,[=](){
        this->hide();
        this->timer=new TimerScene();
        this->timer->setGeometry(this->geometry());
        this->timer->show ();
        //计时页面按钮设置(返回)
        connect(this->timer,&TimerScene::chooseSceneBack,[=](){
            this->setGeometry(this->timer->geometry());
            this->show();
            this->timer->hide();

        });
    });


}


void Lottery::LuanXu(QString *a, int length)
{

    for(int i=0;i<length;i++)
    {
        QTime t;
        t= QTime::currentTime();
        qsrand(t.msec()+t.second()*1000);
        int r = i+qrand()%(length-i);
        QString temp=a[i];
        a[i]=a[r];
        a[r]=temp;
    }
}

void Lottery::delete_item(QString *a, QString item, int &recordNum)
{
      for(int i=0;i <recordNum;i++)
      {
        if(a[i]==item)
        {
          for(int j=i;j <recordNum;j++)
          {
              a[j]=a[j+1];
          }
          recordNum--;
        }
      }
}
Lottery::~Lottery()
{
    delete ui;
}

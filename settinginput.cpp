#include "settinginput.h"
#include<QMenu>
#include<QMenuBar>
#include<mypushbutton.h>
#include<QTimer>
#include<QInputDialog>
#include<QLabel>
#include<QLineEdit>
#include<QFile>
#include<QDebug>
#include<QMessageBox>
#include<QTextCodec>
#include<QTextStream>
#include<QDir>
SettingInput::SettingInput(QWidget *parent) : QMainWindow(parent)
{

}

SettingInput::SettingInput(int index)
{
    this->groupIndex=index;
    this->setFixedSize(400,600);
    QString str=QString("第%1组配置文件的书写").arg(this->groupIndex);
    this->setWindowTitle(str);
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

    //返回按钮的相关配置
    MyPushButton *backBtn= new MyPushButton(":/res/back.png");
    backBtn->setParent(this);
    backBtn->move(260,this->height()-backBtn->height()-20);

    connect(backBtn,&MyPushButton::clicked,[=](){
        backBtn->Zoom1();
        backBtn->Zoom2();
        QTimer::singleShot(500,this,[=](){
            emit this->chooseSceneBack();
        });

    });





    //标题提示Label的创建与显示
    QLabel *title=new QLabel;
    title->resize(200,30);
    QFont fontTitle;
    fontTitle.setPointSize(10);
    fontTitle.setFamily("宋体");
    fontTitle.setBold(true);
    title->setFont(fontTitle);
    QString strTitle;
    strTitle=QString("第%1组人员名单书写").arg(this->groupIndex);
    title->setAlignment(Qt::AlignCenter);
    title->setParent(this);
    title->move(100,50);
    title->setText(str);

    //编辑输入框的创建
    for(int i=0;i<16;i++)
    {
        QLabel *label=new QLabel;
        label->setParent(this);
        label->resize(50,30);
        QString personName=QString("姓名%1").arg(i+1);
        label->setText(personName);
        label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
        label->move(25+i%2*190,100+i/2*50);
        QLineEdit *edit=new QLineEdit;
        edit->setParent(this);
        edit->resize(80,30);
        edit->move(90+i%2*190,100+i/2*50);
        //edit->show();
        this->editItem[i]=edit;

    }


    //判断配置文件夹目录是否存在，若不存在则创建
    QString dir_str = "../QtChoose/file";
    QDir dir;
    if (!dir.exists(dir_str))
    {
        bool res = dir.mkpath(dir_str);
        qDebug() << "新建目录是否成功" << res;
    }

    QString route;
    route=QString("../QtChoose/file/%1.txt").arg(this->groupIndex);
    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
    QFile file(route);
    file.setParent(this);
    file.open(QIODevice::ReadOnly);
    QByteArray arr[17];
    int line=0;
    if(!file.isOpen())
    {
        QMessageBox::critical(this,"打开错误","找不到所需要的文件——若第一次填写该组配置时出现，属于正常情况，继续即可！");
    }

    while(!file.atEnd())
    {
        arr[line]=file.readLine();
        this->editItem[line]->setText(codec->toUnicode(arr[line]));
        line++;
    }
    file.close();





    //确认按钮的相关配置（写入数据）
    this->confirm=new MyPushButton(":/res/matchright.png");
    this->confirm->setParent(this);
    this->confirm->move(60,this->height()-backBtn->height()-20);
    connect(confirm,&MyPushButton::clicked,[=](){
        this->confirm->Zoom1();
        this->confirm->Zoom2();
        QString route;
        route=QString("../QtChoose/file/%1.txt").arg(this->groupIndex);
        QFile file(route);
        file.open(QIODevice::WriteOnly|QFile::Truncate);

        if(!file.isOpen())
        {
            QMessageBox::critical(this,"打开错误","找不到所需要的文件，请查看软件目录下是否存在file文件夹，若没有请创建！");

        }

        for(int i=0;i<16;i++)
        {
            this->theChooseName[i]=this->editItem[i]->text();
            QTextStream out(&file);
            out.setCodec("UTF-8");
            if(this->theChooseName[i]!="")
            {
                if(this->theChooseName[i].endsWith("\r\n"))
                {
                    out<<this->theChooseName[i];
                }
                else
                {
                    out<<this->theChooseName[i]<<"\r\n";
                }
            }
            else
            {
                continue;
            }
        }
        file.close();
        QMessageBox::information(this,"保存提示","保存成功，请返回主界面开始选择！");
//        QTimer::singleShot(500,[=](){
//            emit this->chooseSceneStart();
//        });
    });

}

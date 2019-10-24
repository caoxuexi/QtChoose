#include "settingscene.h"
#include <mypushbutton.h>
#include<QMenuBar>
#include<QMenu>
#include<QLabel>
#include<QDebug>
#include<QFont>
#include<QTimer>
#include<settinginput.h>
#include<QMessageBox>
SettingScene::SettingScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(400,600);
    this->setWindowTitle("选择需要配置的组");
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

    //设置组图片选择按钮
    for(int i=0;i<6;i++)
    {
        QString picture=QString(":/res/%1.png").arg(i+1);
        MyPushButton *group=new MyPushButton(picture);
        group->setParent(this);
        group->move(50+i%2*200,50+i/2*150);
        QLabel *label=new QLabel;
        label->resize(group->size());
        label->setParent(this);
        label->move(50+i%2*200,60+i/2*150);
        label->setFixedSize(group->width(),group->height());
        QFont font;
        font.setFamily("汉呈波波行书");
        font.setPointSize(20);
        label->setFont(font);
        label->setText(QString::number(i+1));

        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
        connect(group,&MyPushButton::clicked,[=](){
            //选择组
            //qDebug()<<"选择了组"<<i+1;
            group->Zoom1();
            group->Zoom2();
            QTimer::singleShot(500,this,[=](){
                this->hide();
                this->input=new SettingInput(i+1);
                this->input->setGeometry(this->geometry());
                this->input->show();

                //设置返回
                connect(this->input,&SettingInput::chooseSceneBack,[=](){
                    this->setGeometry(input->geometry());
                    this->input->hide();
                    this->show();
                });
            });
        });
    }
}

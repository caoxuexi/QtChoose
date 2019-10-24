#include "choosescene.h"
#include "mypushbutton.h"
#include<QMenuBar>
#include<QMenu>
#include<QLabel>
#include<QDebug>
#include<QFont>
#include<QTimer>
#include<QMessageBox>

ChooseScene::ChooseScene(QWidget *parent) : QMainWindow(parent)
{
    this->setFixedSize(400,600);
    this->setWindowTitle("选择使用的组");
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



    for(int i=0;i<6;i++)
    {
        MyPushButton *group=new MyPushButton(":/res/solidHeart.png");
        group->setParent(this);
        group->move(50+i%2*200,100+i/2*150);
        QLabel *label=new QLabel;
        label->setParent(this);
        label->move(50+i%2*200,100+i/2*150);
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
            this->hide();
            this->lottery=new Lottery(i+1);
            this->lottery->setGeometry(this->geometry());
            this->lottery->show();

            //设置返回
            connect(this->lottery,&Lottery::chooseSceneBack,[=](){
                this->setGeometry(lottery->geometry());
                this->show();
                this->lottery->hide();

            });
            qDebug()<<"选择了组"<<i+1;
        });

    }

}

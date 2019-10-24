#include "mypushbutton.h"
#include<QPixmap>
#include<QPropertyAnimation>
#include<QDebug>
MyPushButton::MyPushButton(QPushButton *parent) : QPushButton(parent)
{

}



MyPushButton::MyPushButton(QString normalImg,QString pressImg)
{
        this->normalImgPath = normalImg;
        this->pressImgPath = pressImg;

        //显示不规则按钮
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            QString str = QString("路径加载失败：%1").arg(this->normalImgPath);
            qDebug() << str;
            return;
        }

        //1、设置图片固定尺寸
        this->setFixedSize( pix.width(),pix.height());

        //2、设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //3、设置图标
        this->setIcon(pix);

        //4、设置图标尺寸
        this->setIconSize(QSize(pix.width(),pix.height()));

}

void MyPushButton::Zoom1()
{
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //创建时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);//执行动画执行完时删除动画
}

void MyPushButton::Zoom2()
{
    //创建动画对象
    QPropertyAnimation *animation=new QPropertyAnimation(this,"geometry");
    //创建时间间隔
    animation->setDuration(200);
    //设置起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //设置结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start(QAbstractAnimation::DeleteWhenStopped);//执行动画执行完时删除动画
}

void MyPushButton::mousePressEvent(QMouseEvent *e)
{
    if(this->pressImgPath!="")
    {
        QPixmap pix;
        bool ret = pix.load(this->pressImgPath);
        if(!ret)
        {
            QString str = QString("路径加载失败：%1").arg(this->pressImgPath);
            qDebug() << str;
            return;
        }

        //1、设置图片固定尺寸
        this->setFixedSize( pix.width(),pix.height());

        //2、设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //3、设置图标
        this->setIcon(pix);

        //4、设置图标尺寸
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //其他事情交换父类
    return QPushButton::mousePressEvent(e);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *e)
{
    if(this->normalImgPath != "") //路径不为空，切图
    {
        //显示不规则按钮
        QPixmap pix;
        bool ret = pix.load(this->normalImgPath);
        if(!ret)
        {
            QString str = QString("路径加载失败：%1").arg(this->normalImgPath);
            qDebug() << str;
            return;
        }

        //1、设置图片固定尺寸
        this->setFixedSize( pix.width(),pix.height());

        //2、设置不规则样式
        this->setStyleSheet("QPushButton{border:0px;}");

        //3、设置图标
        this->setIcon(pix);

        //4、设置图标尺寸
        this->setIconSize(QSize(pix.width(),pix.height()));
    }


    //其他事情交换父类
    return QPushButton::mouseReleaseEvent(e);

}

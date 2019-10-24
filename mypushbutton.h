#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>


class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    explicit MyPushButton(QPushButton *parent = nullptr);

    MyPushButton(QString normalImg,QString pressImg="");
    void Zoom1();
    void Zoom2();
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    QString normalImgPath;
    QString pressImgPath;
signals:

public slots:
};

#endif // MYPUSHBUTTON_H

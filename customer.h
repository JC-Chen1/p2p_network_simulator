
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDebug>


class customer //: public QWidget
{
    //Q_OBJECT
public:
    //explicit customer(QWidget *parent = nullptr);
    customer();
    QPushButton* button;  //label指针成员 用于存放图片
    int posX;
    int posY;
    void setID(int i);
    int id; //客户机唯一标识符
private:


//signals:

};

#endif // CUSTOMER_H

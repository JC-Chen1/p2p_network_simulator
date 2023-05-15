#include "customer.h"

customer::customer(/*QWidget *parent*/)
   // : QWidget{parent}
{
    QPushButton* btn = new QPushButton();
    btn->setStyleSheet("background:transparent;border-image: url(:/customer_red.png);");
    button = btn;
    //id默认值
    id = -1;
}

void customer::setID(int i){
    id = i;
}

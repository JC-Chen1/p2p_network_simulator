
#include "node.h"
#include<random>
#include<ctime>

//初始化坐标函数
Node::Node(int num) {
    //把所有坐标限定在（1000，1000）以内
    std::random_device rd;
    x = rd() % 3000;
    srand(time(0) + rand());//根据获得的随机x坐标，再和time获得y坐标
    y = rand()%3000;
    //设置客户端或服务器顶点的编号
    //默认服务器顶点为0，客户端顶点为1到N
    nodeNum = num;
    //设置按钮
    QPushButton* btn = new QPushButton();
    btn->setStyleSheet("background:transparent;border-image: url(:/client_1.png);");
    button = btn;
}

Node::Node(int x,int y){
    this->x=x;
    this->y=y;
}


#ifndef NODE_H
#define NODE_H


#include <QObject>
#include<QWidget>
#include<QLabel>
#include<QPushButton>
#include<QDebug>


class Node
{
public:
    //构造函数生成随机坐标
    Node(int num);
    Node(int x,int y);
    Node(int x,int y,int num):x(x),y(y),nodeNum(num) {}
    Node() {};
    //顶点坐标
    int x;
    int y;
    //顶点的编号
    int nodeNum;
    //按钮
    QPushButton* button;  //label指针成员 用于存放图片
};

#endif // NODE_H

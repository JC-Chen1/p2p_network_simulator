
#ifndef CONNECTION_H
#define CONNECTION_H


#include<iostream>
#include"Node.h"

//定义连接类，用于连接图的构建
//连接类的初始化连接在main函数中进行传入
class Connection {
public:
    Connection(int n1, int n2, int rate);
    int node1_index;
    int node2_index;
    //表示点之间的传输速度
    int trans_rate;
};


#endif // CONNECTION_H

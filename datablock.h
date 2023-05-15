
#ifndef DATABLOCK_H
#define DATABLOCK_H

#include<iostream>
class DataBlock {
public:
    DataBlock(int num = INT_MAX);
    //数据块的编号
    int dataNum;
    //数据块传输进来的时间
    double time = 0;
    //设置函数
    void setTime(double t) { time = t; }
};

#endif // DATABLOCK_H

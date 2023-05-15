
#ifndef SERVERNODE_H
#define SERVERNODE_H
#include"Node.h"
#include"DataBlock.h"
#include<vector>
#include <chrono>
#include <thread>
using namespace std;

class ServerNode :public Node {
public:
    ServerNode(int size);
    ServerNode() {};
    //视频数据块缓存区大小
    int serverSize;
    static int globalDataNum; // 全局唯一整数序号
    bool keepUpdating; // 控制更新循环的标志
    //服务器产生的视频数据块缓存区，用一个vector来存放
    //一个DataBlock代表1KByte的数据
    vector<DataBlock> dataBuffer;
    //每秒产生数据并且对服务器存储的视频数据进行更新的函数
    void updateVideoData();
    //开始更新数据块的函数
    //使用 C++11 的 <chrono> 和 <thread> 库
    void startUpdatingVideoData();
    //停止更新
    void stopUpdatingVideoData();
    //可以在主函数中使用下面语句调用
    // server.startUpdatingVideoData(); // 开始每秒钟调用 updateVideoData
    // 假设程序运行10秒后终止更新
    //this_thread::sleep_for(chrono::seconds(10));
    //server.stopUpdatingVideoData();
};


#endif // SERVERNODE_H

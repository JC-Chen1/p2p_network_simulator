
#ifndef CLIENTNODE_H
#define CLIENTNODE_H
#include<iostream>
#include<vector>
#include"Node.h"
#include"DataBlock.h"
#include"Connection.h"
#include"PlayableSegment.h"
#include"ServerNode.h"
#include<unordered_set>
using namespace std;

class ClientNode :public Node {
public:
    ClientNode(int size,int num,int xx,int yy);
    ClientNode() { contiousPlayTime = 0; };
    //流畅度

    //客户端可缓存的大小
    int bufferSize;
    // 控制更新循环的标志
    bool keepUpdating;
    // 客户端的连续播放时间
    double contiousPlayTime=0;
    // 客户端的最后一个数据块的播放时间
    double endPlayTime = 1000000;
    // 记录当前时间，每当updatebuffer的时候更新，方便计算数据块的播放时间
    double curTime = 0;
    //已播放的视频块
    unordered_set<int> playedBlock;
    // 记录每个数据块的播放时间
    vector<pair<int, double>> playTimeMemory;
    //缓冲容器
    vector<DataBlock> dataBuffer;
    //存放连续数据块相关信息的vector
    vector<PlayableSegment> continuous_segments;
    //向邻居获取并且更新缓存区的函数
    void updateBuffer(double preTime,vector<ClientNode>& all_nodes, vector<Connection>& connections, ServerNode& server);
    //检查是否能连续播放的函数并且测试流畅度
    void isPlaySmoothly();
    //添加视频块到buffer的函数
    void addDataBlock(DataBlock block);
    //检查缓冲区中是否存在连续的M个数据块
    void checkContinuousPlayability(int min_continuous_blocks = 5);
    //从服务器获取数据块
    void getFromServer(double preTime, ServerNode& connected_node,int trans_rate);
    //从客户端获取数据块
    void getFromClient(double preTime, ClientNode& connected_node,int trans_rate);
    //播放视频块
    void play(PlayableSegment blocks);
    //清空记录模块
    void reset();
    ////开始获取数据块的控制函数
    //void startUpdatingBuffer(vector<ClientNode>& all_client_nodes, vector<Connection>& connections, ServerNode& server);
    ////停止获取数据块的控制函数
    //void stopUpdatingBuffer();
    //可以在主函数中使用下面语句调用
    //client.startUpdatingBuffer(all_client_nodes, connections, server); // 开始每秒钟调用 updateBuffer
    //假设程序运行10秒后终止更新
    //this_thread::sleep_for(chrono::seconds(10));
    //client.stopUpdatingBuffer();
};

#endif // CLIENTNODE_H

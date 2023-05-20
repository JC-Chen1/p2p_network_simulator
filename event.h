
#ifndef EVENT_H
#define EVENT_H

#include "DataBlock.h"
#include<unordered_map>
#include<queue>
#include"ClientNode.h"
#include"ServerNode.h"
using namespace std;

// 定义事件的基类
class Event {
public:
    double time; // 事件发生时间
    virtual void execute() = 0; // 执行事件的操作
    int id;
    Event(int id1) {
        id = id1;
    }
    Event();
};

struct cmp {
    bool operator() (const Event* a, const Event* b) const {
        return a->time > b->time;
    }
};


// 定义服务器产生视频块事件
class GenerateVideoBlockEvent : public Event {
public:
    //换成一个服务器节点，调用里面的缓冲容器dataBuffer
    ServerNode& server_node;
    priority_queue<Event*, vector< Event*>, cmp>& eventList;
    GenerateVideoBlockEvent(ServerNode& node,priority_queue<Event*, vector< Event*>, cmp>& el):server_node(node),eventList(el){};
    GenerateVideoBlockEvent(double t, ServerNode& server,int id,priority_queue<Event*, vector< Event*>, cmp>& el):Event(id), server_node(server),eventList(el) {
        time = t;
    }
    void execute() override {
        // 生成新的视频块
        //调用servernode的生成数据块函数
        server_node.updateVideoData();

        // blockMap_->insert({newBlock.dataNum, newBlock});

        // 添加新的GenerateVideoBlockEvent事件到事件列表中
        qDebug() << "服务器在" << time << "秒时加入队列，进行更新";
        double newTime = time + 1; // 1秒后
//        for (int i = 0; i < server_node.dataBuffer.size(); i++) {
//            qDebug() << "输出此时服务器的数据块编号:" << server_node.dataBuffer[i].dataNum;
//        }
        GenerateVideoBlockEvent* newEvent = new GenerateVideoBlockEvent(newTime, server_node,0,eventList);
        //暂时先跑20
            eventList.push(newEvent);
    }
private:
    //unordered_map <int, DataBlock>* blockMap_;

    int clientNum;
};

// 客户端接收事件
class RequestVideoBlockEvent : public Event {
public:
    RequestVideoBlockEvent(double t, int clientNum, ClientNode& client, vector<ClientNode>& nodeList, vector<Connection>& connections, ServerNode& server,priority_queue<Event*, vector< Event*>, cmp>& el) :Event(clientNum + 1), server_(server), client_(client), nodeList_(nodeList), connections_(connections),eventList(el) {
        time = t;
        //blockId_ = blockId;
        //client_表示当前发起请求的客户端节点

        //clientNum表示当前客户端节点的编号（在ClientNode数组中）
        this->clientNum = clientNum;
        //客户端节点列表

        //连接关系


    }
    void execute() override {
        client_.updateBuffer(time, nodeList_, connections_, server_);
        //qDebug() << "在" << QString::number(time) << "秒时客户端" << QString::number(clientNum) << "号完成请求和更新";
//        for (int i = 0; i < client_.dataBuffer.size(); i++) {
//            qDebug() << "数据块编号为：" << QString::number(client_.dataBuffer[i].dataNum) << ",生成时间为：" << QString::number(client_.dataBuffer[i].time);
//        }
        // 添加新的RequestVideoBlockEvent事件到邻居节点的事件列表中
        double newTime = time + 0.5; // 0.5秒后
        //Node类中有定义nodeNum来记录节点的编号，并且也是节点在总节点列表中的下标
        //客户端节点在客户端节点列表的下标 = nodeNum - 1（因为nodeNum包含服务器节点的下标）
        //定时发起检查的请求
        //push0.01秒后的新事件
        RequestVideoBlockEvent* newEvent = new RequestVideoBlockEvent(newTime, client_.nodeNum - 1, nodeList_[client_.nodeNum - 1], nodeList_, connections_, server_,eventList);
         eventList.push(newEvent);
    }

private:

    ClientNode& client_;
    int clientNum;
    vector<ClientNode>& nodeList_;
    vector<Connection>& connections_;
    ServerNode& server_;
    priority_queue<Event*, vector< Event*>, cmp>& eventList;
};

#endif // EVENT_H

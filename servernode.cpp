#include"ServerNode.h"
//默认服务器在node总结点数组中为0号下标
ServerNode::ServerNode(int size) :Node(0) {
    //设置服务器存放产生视频数据的容器大小
    serverSize = size;
}

void ServerNode::updateVideoData() {
    // 每秒产生 30 个数据块 (30 KByte)
    for (int i = 0; i < 30; ++i) {
        DataBlock newDataBlock(++globalDataNum);

        // 将新数据块添加到缓存区
        dataBuffer.push_back(newDataBlock);

        // 如果缓存区超过大小限制，删除最旧的数据块
        if (dataBuffer.size() > serverSize) {
            dataBuffer.erase(dataBuffer.begin());
        }
    }
}

void ServerNode::startUpdatingVideoData() {
    keepUpdating = true;
    // 创建一个新线程，每秒钟调用一次 updateVideoData 函数
    thread updateThread([this]() {
        while (keepUpdating) {
            this->updateVideoData();
            this_thread::sleep_for(chrono::seconds(1));
        }
    });
    updateThread.detach(); // 分离线程，让它独立运行
}

void ServerNode::stopUpdatingVideoData() {
    keepUpdating = false; // 设置标志以终止更新循环
}

int ServerNode::globalDataNum = 0;

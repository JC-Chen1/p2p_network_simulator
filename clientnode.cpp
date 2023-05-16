#include"ClientNode.h"
#include"ServerNode.h"
#include<algorithm>

ClientNode::ClientNode(int size, int num,int xx, int yy) :Node(num) {
    bufferSize = size;
    contiousPlayTime = 0;
    x = xx;
    y = yy;
}

void ClientNode::getFromClient(double preTime, ClientNode& connected_node, int trans_rate) {
    //记录已传输的数据块个数
    int transferred_blocks = 0;
    for (const auto& block : connected_node.dataBuffer) {
        //使用std::find_if算法从dataBuffer容器中查找与给定的block具有相同dataNum的DataBlock对象
        //通过将这个表达式与dataBuffer.end()进行比较，可以得出一个布尔值。
        //如果表达式结果为true，说明在dataBuffer中没有找到与block具有相同dataNum的数据块；如果结果为false，则表示已经找到了这样的数据块。
        if ((find_if(dataBuffer.begin(), dataBuffer.end(),
                     [&block](const DataBlock& existing_block) {
                         return existing_block.dataNum == block.dataNum;
                     }) == dataBuffer.end())&&block.dataNum != INT_MAX) {
            //已传输数据块个数++
            transferred_blocks++;
        }
    }
    double new_time = (double)transferred_blocks / trans_rate + preTime;
    for ( auto& block : connected_node.dataBuffer) {
        if ((find_if(dataBuffer.begin(), dataBuffer.end(),
                     [&block](const DataBlock& existing_block) {
                         return existing_block.dataNum == block.dataNum;
                     }) == dataBuffer.end()) && block.dataNum != INT_MAX) {
            block.setTime(new_time);
            //将自己没有的数据块添加到自己的dataBuffer中
            addDataBlock(block);
        }
    }
    curTime = new_time;
}

void ClientNode::play(PlayableSegment blocks)
{
    qDebug()<< "enter play";
    //默认播放速度是30
    contiousPlayTime += blocks.length / 30.0;
    qDebug() << "contiousplaytime:" << contiousPlayTime;
    //将已播放的数据块记录下来
    for (int i = 0; i < blocks.length; ++i) {
        playedBlock.insert(blocks.start_block_id + i);
        // todo记录每个数据块的播放时间
        double play_time = curTime + i / 30.0;
        playTimeMemory.emplace_back(make_pair(blocks.start_block_id + i, play_time));
        if (i == blocks.length - 1) {
            endPlayTime = play_time;
        }
    }
}

void ClientNode::reset()
{
    playedBlock.clear();
    playTimeMemory.clear();
    contiousPlayTime = 0;
    dataBuffer.clear();
    curTime = 0;
    endPlayTime = 100000;
}

void ClientNode::getFromServer(double preTime, ServerNode& connected_node,int trans_rate) {
    curTime = preTime;
    //记录已传输的数据块个数
    int transferred_blocks = 0;
    for (const auto& block : connected_node.dataBuffer) {
        //使用std::find_if算法从dataBuffer容器中查找与给定的block具有相同dataNum的DataBlock对象
        //通过将这个表达式与dataBuffer.end()进行比较，可以得出一个布尔值。
        //如果表达式结果为true，说明在dataBuffer中没有找到与block具有相同dataNum的数据块；如果结果为false，则表示已经找到了这样的数据块。
        if ((find_if(dataBuffer.begin(), dataBuffer.end(),
                     [&block](const DataBlock& existing_block) {
                         return existing_block.dataNum == block.dataNum;
                     }) == dataBuffer.end()) && block.dataNum != INT_MAX) {
            //已传输数据块个数++
            transferred_blocks++;
        }
    }
    double new_time = (double)transferred_blocks / trans_rate + preTime;
    for (auto& block : connected_node.dataBuffer) {
        if ((find_if(dataBuffer.begin(), dataBuffer.end(),
                     [&block](const DataBlock& existing_block) {
                         return existing_block.dataNum == block.dataNum;
                     }) == dataBuffer.end()) && block.dataNum != INT_MAX) {
            block.setTime(new_time);
            //将自己没有的数据块添加到自己的dataBuffer中
            addDataBlock(block);
        }
    }
    curTime = new_time;
}

void ClientNode::updateBuffer(double preTime, vector<ClientNode>& all_client_nodes, vector<Connection>& connections, ServerNode& server) {
    //对当前节点遍历连接关系容器
    for (const auto& connection : connections) {
        //如果作为连接的一端
        if (connection.node1_index == nodeNum) {
            //如果连接的节点是服务器(在Node容器中下标为0)
            if (connection.node2_index == 0) {
                ServerNode& connected_node = server;
                //遍历该节点数据块缓冲区
                getFromServer(preTime, connected_node, connection.trans_rate);
            }
            //否则就为客户端节点
            //用一个临时常量来存被链接的节点
            else {
                ClientNode& connected_node = all_client_nodes[connection.node2_index - 1];
                getFromClient(preTime, connected_node, connection.trans_rate);
            }
        }
        else  if (connection.node2_index == nodeNum) {
            //如果连接的节点是服务器(在Node容器中下标为0)
            if (connection.node1_index == 0) {
                ServerNode& connected_node = server;
                getFromServer(preTime, connected_node, connection.trans_rate);
            }
            //否则就为客户端节点
            //用一个临时常量来存被链接的节点
            else {
                ClientNode& connected_node = all_client_nodes[connection.node1_index - 1];
                getFromClient(preTime, connected_node, connection.trans_rate);
            }
        }
        // 对缓冲容器中的数据块按照dataNum进行升序排序
        std::sort(dataBuffer.begin(), dataBuffer.end(), [](const DataBlock& a, const DataBlock& b) {
            return a.dataNum < b.dataNum;
        });
    }
//    cout << dataBuffer.size() << endl;
    /*for (int i = 0; i < dataBuffer.size(); i++) {
        cout << dataBuffer[i] << endl;
    }*/
   // qDebug()<< "enter check continuous";
    checkContinuousPlayability();
}

void ClientNode::addDataBlock(DataBlock block) {
    //缓冲队列的大小将始终保持在bufferSize个数据分块以内
    //当添加新数据块时，最老的数据块会被覆盖(先排序，再用erase抹掉第一个数据块（最老的）)
    if (dataBuffer.size() >= bufferSize) {
        sort(dataBuffer.begin(), dataBuffer.end(), [](const DataBlock& a, const DataBlock& b) {
            return a.dataNum < b.dataNum;
        });
        if (dataBuffer.size() > 0 && playedBlock.find(dataBuffer[0].dataNum) != playedBlock.end()) {
            dataBuffer.erase(dataBuffer.begin());
        }
        else {
            return;
        }

    }
    dataBuffer.push_back(block);
}

void ClientNode::checkContinuousPlayability(int min_continuous_blocks ) {
    if (dataBuffer.empty()) {
        return;
    }
    //对dataBuffer按照数据块编号进行排序
    sort(dataBuffer.begin(), dataBuffer.end(), [](const DataBlock& a, const DataBlock& b) {
        return a.dataNum < b.dataNum;
    });

    // 找到第一个没有播放过的数据块
    size_t i = 0;
    for (; i < dataBuffer.size(); ++i) {
        if (playedBlock.find(dataBuffer[i].dataNum) == playedBlock.end()) {
            break;
        }
    }
    if (i == dataBuffer.size()) {
        return;
    }
    int start_block_id = dataBuffer[i].dataNum;
    int current_block_id = start_block_id;
    int count = 1;
    ++i;
    //检查相邻数据块之间的编号差异
    for (; i < dataBuffer.size(); ++i) {
        // 播放应该是连续播放
        if (dataBuffer[i].dataNum == current_block_id + 1 && playedBlock.find(dataBuffer[i].dataNum) == playedBlock.end()) {
            count++;
        }
        else {
            //当发现连续M个或更多数据块时，将其起始编号及长度记录到continuous_segments向量中。
            // 应该是只播放找到的第一个连续块
            if (count >= min_continuous_blocks) {

                // continuous_segments.push_back(PlayableSegment(start_block_id, count));
                break;
            }
            start_block_id = dataBuffer[i].dataNum;
            count = 1;
        }
        current_block_id = dataBuffer[i].dataNum;
    }
    if (count >= 5) {
        // 播放数据块
        play(PlayableSegment(start_block_id, count));

//        for (int i = 0; i < dataBuffer.size(); i++) {
//            qDebug() << dataBuffer[i].dataNum;
//        }
//        cout << endl;
    }
//    cout << start_block_id << " " << count << endl;

    return;
}

//void ClientNode::startUpdatingBuffer(vector<ClientNode>& all_client_nodes, vector<Connection>& connections, ServerNode& server) {
//    keepUpdating = true;
//    // 创建一个新线程，每秒钟调用一次 updateBuffer 函数
//    thread updateThread([this, &all_client_nodes, &connections, &server]() {
//        while (keepUpdating) {
//            this->updateBuffer(all_client_nodes, connections, server);
//            this_thread::sleep_for(chrono::seconds(1));
//        }
//        });
//    updateThread.detach(); // 分离线程，让它独立运行
//}

//void ClientNode::stopUpdatingBuffer() {
//    keepUpdating = false; // 设置标志以终止更新循环
//}

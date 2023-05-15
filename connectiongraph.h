
#ifndef CONNECTIONGRAPH_H
#define CONNECTIONGRAPH_H

#include <random>
#include"Connection.h"
#include "Node.h"
using namespace std;

class ConnectionGraph {
public:
    ConnectionGraph(){};
    ConnectionGraph(const vector<vector<int>>& vertices, vector<Node> p);
    //邻接矩阵记录连接情况
    vector<vector<int>> m_vertices;
    //存放连接类节点和传输速率相关信息
    vector<Connection> m_connectionList;
    //存放按编号顺序排列的节点数组
    vector<Node> m_p2p;
    //添加连接关系的函数
    void addConnection(int node1, int node2, int rate);
    //设置邻接矩阵
    void setAdjMatrix();
    //随机选择t个节点连接的函数
    bool connectNodes(int node, int t);
    //基于维诺图建立连接（整个图）
    bool VNconnect();
    //删除对应某个节点的连接
    bool deleteConnection(int node);
};

#endif // CONNECTIONGRAPH_H

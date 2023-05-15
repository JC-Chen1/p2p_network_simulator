#include"ConnectionGraph.h"
#include "Voronoi.h"
#include<cmath>
ConnectionGraph::ConnectionGraph(const vector<vector<int>>& vertices, vector<Node> p) {
    m_vertices = vertices;
    m_p2p = p;
}

void ConnectionGraph::addConnection(int node1, int node2, int rate) {
    m_connectionList.push_back({ node1, node2, rate });
}

bool ConnectionGraph::connectNodes(int node, int t) {
    //default_random_engine e;
    //uniform_int_distribution<int> dis(0, m_vertices[0].size() - 1);
    random_device rd;
    //对节点数组中的每个节点随机设置连接
    //for (int i = 0; i < m_p2p.size(); i++) {
    //    if (i != node) {
    while (t!=0) {
        //每次随机挑选t个节点来连接
        //确定随机节点的在邻接矩阵和节点数组中的下标
        /*int rdNodeIndex = dis(e);*/
        int rdNodeIndex = rd() % m_vertices[0].size();
        //判断随机选的节点是否与当前节点相同，若相同则跳过
        if (node == rdNodeIndex) continue;
        //首先计算传输速率rate
        Node node1 = m_p2p[node];
        Node node2 = m_p2p[rdNodeIndex];
        double standDistance = sqrt(1000 * 1000 + 1000 * 1000);
        //计算出标准距离和两点距离的比例，用1减去表示成反比
        double distancePer = 1 - sqrt(pow((node1.x - node2.x), 2) + pow((node1.y - node2.y), 2)) / standDistance;
        int rate = int((100 - 20) * distancePer + 20);
        bool flag = false;
        for (vector<Connection>::iterator it = m_connectionList.begin(); it != m_connectionList.end(); ++it) {
            //查找，如果连接关系列表中已经存在该连接，则跳过
            if ((it->node1_index == node && it->node2_index == rdNodeIndex) || (it->node2_index == node && it->node1_index == rdNodeIndex)) {
                flag = true;
                if (node != 0) t--;
                //cout << "已存在连接" << it->node1_index << " " << it->node2_index << endl;
                break;
            }
        }
        if (!flag) {
            //若没查找到该关系则添加进连接关系信息表
            m_connectionList.insert(m_connectionList.end(), { node,rdNodeIndex , rate });
            t--;
            // cout <<node << "创建了新边" << node << " "<< rdNodeIndex << " " << t << endl;
        }
    }
    //}
    //}
    return true;
}

void ConnectionGraph::setAdjMatrix() {
    for (vector<Connection>::iterator it = m_connectionList.begin(); it != m_connectionList.end(); ++it) {
        m_vertices[it->node1_index][it->node2_index] = m_vertices[it->node2_index][it->node1_index] = 1;
    }
}

bool ConnectionGraph::VNconnect() {
    m_connectionList.clear();
    Voronoi vngraph=Voronoi(0,1000,0,1000,m_p2p);
    // vector<vector<int>> neighbors=vngraph.get_neibour();
    vector<vector<int>> neighbors = vngraph.find_neighbors_all();
    double standDistance = sqrt(1000 * 1000 + 1000 * 1000);
    // build connection
    for(int i=0;i<m_p2p.size();i++){
        vector<int> nei=neighbors[i];
        cout << "nei.size:" << nei.size() << endl;
        for(int j=0;j<nei.size();j++){
            Node node1=m_p2p[i];
            Node node2=m_p2p[nei[j]];

            //计算出标准距离和两点距离的比例，用1减去表示成反比
            double distancePer = 1 - sqrt(pow((node1.x - node2.x), 2) + pow((node1.y - node2.y), 2)) / standDistance;
            double rate = (100 - 20) * distancePer + 20;
            addConnection(i,nei[j],rate);
        }
    }
    return true;
}

bool ConnectionGraph::deleteConnection(int node)
{

    // 处理m_connectionList
    for (vector<Connection>::iterator it = m_connectionList.begin(); it != m_connectionList.end(); ) {

        if (it->node1_index == node) {
            it=m_connectionList.erase(it);
        }
        else if (it->node2_index == node) {
            it=m_connectionList.erase(it);
        }
        else {
            //将大于要删除节点的节点index-1
            if (it->node1_index > node) {
                it->node1_index -= 1;
            }
            if (it->node2_index > node) {
                it->node2_index -= 1;
            }
            ++it;
        }
    }

    // 将邻接表size-1
    m_vertices = vector<vector<int>>(m_vertices.size() - 1, vector<int>(m_vertices.size() - 1, 0));
    // 处理邻接表
    setAdjMatrix();


    return true;
}

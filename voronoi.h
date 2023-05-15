
#ifndef VORONOI_H
#define VORONOI_H

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include "Node.h"

using namespace std;


// 定义边的结构体
struct Edge {
    Node start, end;
    Edge(Node start, Node end) : start(start), end(end) {}
};

// 定义维诺图的边的结构体
struct VoronoiEdge {
    Node start, end;
    int site1, site2;
    VoronoiEdge(Node start, Node end, int site1, int site2) : start(start), end(end), site1(site1), site2(site2) {}
};

// 定义维诺图的区域的结构体
struct VoronoiRegion {
    vector<Node> vertices;
    int site;
    VoronoiRegion(int site) : site(site) {}
    VoronoiRegion() {}
};



class Voronoi{
public:
    Voronoi(double minX,double maxX,double minY,double maxY,vector<Node>& sites);
    vector<Node> sites;
    double minX,maxX,minY,maxY;
    vector<VoronoiEdge> computeVoronoiEdges();
    vector<vector<int>> get_neibour();
    vector<vector<int>> find_neighbors_all();
    int find_nearest_v(Node& ind, vector<bool>& used);
    int find_nearest_v_ij(Node& ind, vector<bool>& used, int p1, int p2);
    vector<int> find_neighbors_v(int i);
};

#endif // VORONOI_H

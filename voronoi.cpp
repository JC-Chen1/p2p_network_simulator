#include "Voronoi.h"
#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;


// 计算两点之间的距离
double distance(Node p1, Node p2) {
    double dx = p2.x - p1.x;
    double dy = p2.y - p1.y;
    return sqrt(dx * dx + dy * dy);
}

// 计算两条直线的交点
Node intersection(Edge e1, Edge e2) {
    double x1 = e1.start.x;
    double y1 = e1.start.y;
    double x2 = e1.end.x;
    double y2 = e1.end.y;
    double x3 = e2.start.x;
    double y3 = e2.start.y;
    double x4 = e2.end.x;
    double y4 = e2.end.y;
    double den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
    double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / den;
    double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / den;
    return Node(x, y);
}

Voronoi::Voronoi(double minX, double maxX, double minY, double maxY, vector<Node> &sites)
{
    this->minX=minX;
    this->maxX=maxX;
    this->minY=minY;
    this->maxY=maxY;
    this->sites=sites;
}

// 计算维诺图的边
vector<VoronoiEdge> Voronoi::computeVoronoiEdges() {
    // 添加四个虚拟点，表示平面的四个边界
    sites.push_back(Node(minX - 1, minY - 1,-1));
    sites.push_back(Node(minX - 1, maxY + 1,-2));
    sites.push_back(Node(maxX + 1, minY - 1,-3));
    sites.push_back(Node(maxX + 1, maxY + 1,-4));
    // 初始化边界框
    double margin = distance(Node(minX, minY), Node(maxX, maxY));
    Node topLeft(minX - margin, minY - margin);
    Node topRight(maxX + margin, minY - margin);
    Node bottomLeft(minX - margin, maxY + margin);
    Node bottomRight(maxX + margin, maxY + margin);
    // 初始化边界框对应的边
    vector<Edge> edges;
    edges.push_back(Edge(topLeft, topRight));
    edges.push_back(Edge(topRight, bottomRight));
    edges.push_back(Edge(bottomRight, bottomLeft));
    edges.push_back(Edge(bottomLeft, topLeft));
    // 初始化边界框对应的维诺图区域
    vector<VoronoiRegion> regions(sites.size());
    for (int i = 0; i < sites.size(); i++) {
        // 每个region的代号都是
        regions[i].site = sites[i].nodeNum;
        regions[i].vertices.push_back(topLeft);
        regions[i].vertices.push_back(topRight);
        regions[i].vertices.push_back(bottomRight);
        regions[i].vertices.push_back(bottomLeft);
    }
    // 计算维诺图的边
    vector<VoronoiEdge> voronoiEdges;
    for (int i = 0; i < sites.size(); i++) {
        for (int j = i + 1; j < sites.size(); j++) {
            Node site1 = sites[i];
            Node site2 = sites[j];
            Edge edge(site1, site2);
            // 计算边界框和边的交点
            vector<Node> intersections;
            for (int k = 0; k < edges.size(); k++) {
                Node intersectionNode = intersection(edge, edges[k]);
                if (intersectionNode.x != -1 && intersectionNode.y != -1) {
                    intersections.push_back(intersectionNode);
                }
            }
            // 如果交点的个数为奇数，则说明该边在维诺图中
            if (intersections.size() % 2 == 1) {
                Node start = intersections[0];
                Node end = intersections[1];
                int site1Index = i < sites.size() - 4 ? i : (i == sites.size() - 4 ? j : j - 1);
                int site2Index = j < sites.size() - 4 ? j : (j == sites.size() - 4 ? i : i - 1);
                voronoiEdges.push_back(VoronoiEdge(start, end, site1Index, site2Index));
                // 更新维诺图区域
                vector<Node> newVertices;
                newVertices.push_back(start);
                newVertices.push_back(end);
                int currentSite = site1Index;
                int otherSite = site2Index;
                while (currentSite != otherSite) {
                    newVertices.push_back(intersections[2 * (currentSite > otherSite ? currentSite : otherSite) - currentSite - otherSite]);
                    currentSite = currentSite > otherSite ? currentSite - 1 : currentSite + 1;
                }
                regions[site1Index].vertices = newVertices;
                regions[site2Index].vertices = newVertices;
            }
        }
    }
    cout << "voronoi edges size:" << voronoiEdges.size() << endl;
    // 删除虚拟点
    sites.pop_back();
    sites.pop_back();
    sites.pop_back();
    sites.pop_back();
    // 删除边界框对应的维诺图区域
    regions.pop_back();
    regions.pop_back();
    regions.pop_back();
    regions.pop_back();

    // regions.erase(regions.begin(), regions.begin() + 4);
    // 计算每个维诺图区域的顶点
    for (int i = 0; i < voronoiEdges.size(); i++) {
        VoronoiEdge edge = voronoiEdges[i];
        Node mid((edge.start.x + edge.end.x) / 2, (edge.start.y + edge.end.y) / 2);
        regions[edge.site1].vertices.push_back(mid);
        regions[edge.site2].vertices.push_back(mid);
    }
    // 删除重复的顶点
    for (int i = 0; i < regions.size(); i++) {
        vector<Node> vertices = regions[i].vertices;
        vector<Node> newVertices;
        for (int j = 0; j < vertices.size(); j++) {
            bool isDuplicate = false;
            for (int k = 0; k < newVertices.size(); k++) {
                if (distance(vertices[j], newVertices[k]) < 0.00001) {
                    isDuplicate = true;
                    break;
                }
            }
            if (!isDuplicate) {
                newVertices.push_back(vertices[j]);
            }
        }
        regions[i].vertices = newVertices;
    }
    // 返回维诺图的边
    return voronoiEdges;
}

vector<vector<int>> Voronoi::get_neibour()
{
    vector<VoronoiEdge> voronoiEdges = computeVoronoiEdges();
    // 提取每个点的邻居
    vector<vector<int>> neighbors(sites.size());
    for (int i = 0; i < sites.size(); i++) {
        for (int j = 0; j < voronoiEdges.size(); j++) {
            if (voronoiEdges[j].site1 == sites[i].nodeNum) {
                neighbors[i].push_back(voronoiEdges[j].site2);
            }
            if (voronoiEdges[j].site2 == sites[i].nodeNum) {
                neighbors[i].push_back(voronoiEdges[j].site1);
            }
        }
    }
    // 返回每个点的邻居
    return neighbors;
}

int Voronoi::find_nearest_v(Node& ind, vector<bool>& used)
{
    int nei;
    double mindis = 1e300, dis;
    for (int j = 0; j < sites.size(); j++) {
        if (used[j] == 1)continue;
        dis = distance(ind,sites[j]);
        if (dis < mindis) {
            mindis = dis;
            nei = j;
        }
    }
    return nei;
}

int Voronoi::find_nearest_v_ij(Node& ind, vector<bool>& used, int p1, int p2)
{
    int nei;
    double mindis = 1e300, dis;
    for (int j = 0; j < sites.size(); j++) {
        if (used[j] == 1)continue;
        dis = distance(ind,sites[j]);
        if (dis < mindis) {
            mindis = dis;
            nei = j;
        }
        else if (dis - mindis == 0 && (j == p1 || j == p2)) {
            nei = j;
        }
    }
    return nei;
}

vector<int> Voronoi::find_neighbors_v(int i)
{
    vector<int> neibour;

    int nei;

    vector<bool> used = vector<bool>(sites.size(),false);

    Node mid;
    for (int j = 0; j < sites.size(); j++) {
        if (j == i)continue;

        mid.x = (sites[i].x + sites[j].x) / 2.0;
        mid.y = (sites[i].y + sites[j].y) / 2.0;
        //nei = find_nearest_v(mid, used);
        nei = find_nearest_v_ij(mid, used, i, j);
        if (nei == i || nei == j) {
            neibour.push_back(j);
        }
    }
    return neibour;
}

vector<vector<int>> Voronoi::find_neighbors_all()
{
    vector<vector<int>> neighbors(sites.size());
    for (int i = 0; i < sites.size(); i++) {
        neighbors[i] = find_neighbors_v(i);

    }

    return neighbors;
}
//
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <cmath>
//
//using namespace std;
//
//struct Point {
//    double x;
//    double y;
//
//    Point(double x, double y) : x(x), y(y) {}
//
//    bool operator==(const Point& rhs) const {
//        return x == rhs.x && y == rhs.y;
//    }
//
//    bool operator!=(const Point& rhs) const {
//        return !(*this == rhs);
//    }
//};
//
//struct Triangle {
//    Point p1;
//    Point p2;
//    Point p3;
//
//    Triangle(Point p1, Point p2, Point p3) : p1(p1), p2(p2), p3(p3) {}
//
//    bool contains(Point& p) const {
//        double sign1 = (p1.x - p.x) * (p2.y - p1.y) - (p2.x - p1.x) * (p1.y - p.y);
//        double sign2 = (p2.x - p.x) * (p3.y - p2.y) - (p3.x - p2.x) * (p2.y - p.y);
//        double sign3 = (p3.x - p.x) * (p1.y - p3.y) - (p1.x - p3.x) * (p3.y - p.y);
//
//        return (sign1 > 0 && sign2 > 0 && sign3 > 0) || (sign1 < 0 && sign2 < 0 && sign3 < 0);
//    }
//
//    bool operator==(const Triangle& rhs) const {
//        return (p1 == rhs.p1 || p1 == rhs.p2 || p1 == rhs.p3) &&
//            (p2 == rhs.p1 || p2 == rhs.p2 || p2 == rhs.p3) &&
//            (p3 == rhs.p1 || p3 == rhs.p2 || p3 == rhs.p3);
//    }
//};
//
//class DelaunayTriangulation {
//private:
//    vector<Point> points;
//    vector<Triangle> triangles;
//
//    void addPoint(const Point& p) {
//        vector<Triangle> badTriangles;
//
//        for (auto& t : triangles) {
//            if (t.contains(p)) {
//                badTriangles.emplace_back(t);
//            }
//        }
//
//        vector<Triangle> polygon;
//
//        for (auto& t : badTriangles) {
//            for (int i = 0; i < 3; i++) {
//                Triangle edge(t.p1, t.p2, t.p3);
//
//                if (i == 0) {
//                    edge.p1 = t.p1;
//                    edge.p2 = t.p2;
//                }
//                else if (i == 1) {
//                    edge.p1 = t.p2;
//                    edge.p2 = t.p3;
//                }
//                else {
//                    edge.p1 = t.p3;
//                    edge.p2 = t.p1;
//                }
//
//                bool isShared = false;
//                for (auto& bt : badTriangles) {
//                    if (bt == t) {
//                        continue;
//                    }
//
//                    if (bt.contains(edge.p1) && bt.contains(edge.p2)) {
//                        isShared = true;
//                        break;
//                    }
//                }
//
//                if (!isShared) {
//                    polygon.emplace_back(edge);
//                }
//            }
//        }
//
//        for (auto& t : badTriangles) {
//            auto it = find(triangles.begin(), triangles.end(), t);
//            if (it != triangles.end()) {
//                triangles.erase(it);
//            }
//        }
//
//        for (auto& e : polygon) {
//            triangles.emplace_back(e.p1, e.p2, p);
//        }
//    }
//
//public:
//    DelaunayTriangulation(vector<Point> points) : points(points) {
//        Point p1(-1000, -1000);
//        Point p2(1000, -1000);
//        Point p3(0, 1000);
//
//        triangles.emplace_back(p1, p2, p3);
//
//        for (auto& p : points) {
//            addPoint(p);
//        }
//
//        for (auto& t : triangles) {
//            if (t.contains(p1) || t.contains(p2) || t.contains(p3)) {
//                continue;
//            }
//
//            Point center((t.p1.x + t.p2.x + t.p3.x) / 3.0, (t.p1.y + t.p2.y + t.p3.y) / 3.0);
//            bool isBoundingTriangle = false;
//
//            for (auto& p : points) {
//                if ((p == t.p1 || p == t.p2 || p == t.p3) && p != center) {
//                    isBoundingTriangle = true;
//                    break;
//                }
//            }
//
//            if (!isBoundingTriangle) {
//                t.p1 = center;
//                t.p2 = p1;
//                t.p3 = p2;
//            }
//        }
//    }
//
//    void printTriangles() {
//        for (auto& t : triangles) {
//            cout << "Triangle: (" << t.p1.x << ", " << t.p1.y << "), (" << t.p2.x << ", " << t.p2.y << "), (" << t.p3.x << ", " << t.p3.y << ")" << endl;
//        }
//    }
//
//    vector<Point> getVoronoiVertices() {
//        vector<Point> vertices;
//        set<pair<Point, Point>> edges;
//
//        for (auto& t : triangles) {
//            Point center((t.p1.x + t.p2.x + t.p3.x) / 3.0, (t.p1.y + t.p2.y + t.p3.y) / 3.0);
//            Point v1 = getBisector(t.p1, t.p2, center);
//            Point v2 = getBisector(t.p2, t.p3, center);
//            Point v3 = getBisector(t.p3, t.p1, center);
//
//            edges.insert({ v1, v2 });
//            edges.insert({ v2, v3 });
//            edges.insert({ v3, v1 });
//        }
//
//        for (auto& e : edges) {
//            Point p = getIntersection(e, edges);
//            if (p.x != INFINITY && p.y != INFINITY) {
//                vertices.emplace_back(p);
//            }
//        }
//
//        return vertices;
//    }
//
//private:
//    Point getBisector(Point& p1, Point& p2, Point& center) {
//        double a = p2.x - p1.x;
//        double b = p2.y - p1.y;
//        double c = p1.x - center.x;
//        double d = p1.y - center.y;
//
//        double len = sqrt(a * a + b * b);
//        a /= len;
//        b /= len;
//
//        double scale = a * c + b * d;
//
//        return Point(center.x + a * scale, center.y + b * scale);
//    }
//
//    Point getIntersection(pair<Point, Point>& e1, set<pair<Point, Point>>& edges) {
//        double x1 = e1.first.x, y1 = e1.first.y, x2 = e1.second.x, y2 = e1.second.y;
//
//        Point intersection(INFINITY, INFINITY);
//        int count = 0;
//
//        for (auto& e2 : edges) {
//            double x3 = e2.first.x, y3 = e2.first.y, x4 = e2.second.x, y4 = e2.second.y;
//
//            if (x1 == x2) {
//                double m2 = (y4 - y3) / (x4 - x3);
//                double b2 = y3 - m2 * x3;
//                double y = m2 * x1 + b2;
//
//                if ((y >= y3 && y <= y4) || (y >= y4 && y <= y3)) {
//                    count++;
//                    intersection.x += x1;
//                    intersection.y += y;
//                }
//            }
//            else if (x3 == x4) {
//                double m1 = (y2 - y1) / (x2 - x1);
//                double b1 = y1 - m1 * x1;
//                double y = m1 * x3 + b1;
//
//                if ((y >= y1 && y <= y2) || (y >= y2 && y <= y1)) {
//                    count++;
//                    intersection.x += x3;
//                    intersection.y += y;
//                }
//            }
//            else {
//                double m1 = (y2 - y1) / (x2 - x1);
//                double b1 = y1 - m1 * x1;
//
//                double m2 = (y4 - y3) / (x4 - x3);
//                double b2 = y3 - m2 * x3;
//
//                if (m1 == m2) {
//                    continue;
//                }
//
//                double x = (b2 - b1) / (m1 - m2);
//
//                if ((x >= x1 && x <= x2) || (x >= x2 && x <= x1)) {
//                    count++;
//                    intersection.x += x;
//                    intersection.y += m1 * x + b1;
//                }
//            }
//        }
//
//        if (count == 0) {
//            return Point(INFINITY, INFINITY);
//        }
//
//        intersection.x /= count;
//        intersection.y /= count;
//
//        return intersection;
//    }
//};

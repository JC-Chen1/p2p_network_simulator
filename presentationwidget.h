#ifndef PRESENTATIONWIDGET_H
#define PRESENTATIONWIDGET_H

#include <QWidget>
#include<QAbstractScrollArea>
#include<QWheelEvent>
#include<QMouseEvent>
#include<QPaintEvent>
#include<QLabel>
#include <QGraphicsView>
#include <QVector>
#include <QPair>
#include <QLine>
#include <QColor>
#include"customer.h"
#include"clientnode.h"
#include"servernode.h"
#include"connectiongraph.h"
#include"Event.h"

namespace Ui {
class presentationWidget;
}

class presentationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit presentationWidget(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void paintEvent(QPaintEvent* event) override;
    void addLine(int sp,int ep, const QColor& color);
    void removeLine(int node);
    //void deleteCustomer(customer* dc);
    bool deleteNode(int node, ConnectionGraph& graph, vector<Node>& p2p, vector<ClientNode>& clientSet);
    void startEvent();
    void stepEvent_first();
    void stepEvent();
    ~presentationWidget();

    //上一个选中的节点
    int lastChoose;
    //存放所有节点的容器p2p，其中编号为0的为服务器节点
    vector<Node> p2p;
    //初始化一个专门存放客户端节点的容器clientSet
    vector<ClientNode> clientSet;
    //服务器节点
    ServerNode server;
    //节点个数
    int listSize;
    //客户端节点buffer的大小
    int bufferSize;
    //服务器节点buffer的大小
    int server_size;
    //连接图
    ConnectionGraph connectionG;
    //事件队列
    priority_queue<Event*, vector< Event*>, cmp> eventList;
    //模拟事件队列
    GenerateVideoBlockEvent* generateEvent;

public slots:
    void set_ID_text(QString str);
    void set_coordinates_text(QString str);
    void set_data_text(QString str);
    void set_delay_text(QString str);
    void set_fluency_text(QString str);
    void send_information(int choose,vector<DataBlock> block,vector<pair<int, double>> memory);
    void generate(int n);

private slots:

private:
    Ui::presentationWidget *ui;
    //鼠标位移
    QPoint oldPos;
    //客户表
    QList<customer*> list_customer;
    //第一个id
    int firstID = 1;
    bool Pressed;
    //Line类
    struct Line {
        int startPoint;
        int endPoint;
        QLineF line;
        QColor color;
    };
    //存放线的数组
    QVector<Line> m_lines;
};

#endif // PRESENTATIONWIDGET_H

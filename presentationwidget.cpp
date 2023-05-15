#include "presentationwidget.h"
#include "ui_presentationwidget.h"
#include<QPoint>
#include<QRandomGenerator>
#include <QPixmap>
#include"total.h"
#include<vector>

presentationWidget::presentationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::presentationWidget)
{
    ui->setupUi(this);
    Pressed = false;
    lastChoose = -1;
    //节点个数
    listSize = 10;
    //客户端节点buffer的大小
    bufferSize = 30;
    //服务器节点buffer的大小
    server_size = 30;

    //初始化服务器节点
    server = ServerNode(server_size);
    for(int i = 0; i < listSize; i++){
        Node n(i);
        n.button->setParent(this);
        //按编号来初始化客户端节点容器
        if (i != 0) {
            clientSet.push_back(ClientNode(bufferSize, i,n.x,n.y));
        }
        n.button->setGeometry(n.x,n.y,80,80);
        p2p.push_back(n);
    }

    //this->setWindowFlags(Qt::FramelessWindowHint);
}

presentationWidget::~presentationWidget()
{
    delete ui;
}

void presentationWidget::wheelEvent(QWheelEvent *event){

    if (event->modifiers() & Qt::ControlModifier) { // 判断是否按下了 Ctrl 键
        // 获取鼠标当前位置和滚轮方向
        QPoint pos = mapFromGlobal(QCursor::pos());
        int delta = event->angleDelta().y();
        for(int i = 0; i < p2p.size();i++){
            Node n = p2p.at(i);
            //获取原始控件的信息
            QRect rect = n.button->geometry();
            QPoint center = rect.center();
            QSize size = rect.size();
            //计算控件的新大小和位置
            QPoint offset = center - pos;
            QPoint newPos;
            if(delta > 0){
                size *= 1.1;
                newPos = pos + offset * 1.1;
            }
            else{
                size /= 1.1;
                newPos = pos + offset / 1.1;
            }
            rect.setSize(size);
            rect.moveCenter(newPos);
            //更新坐标
            n.x = newPos.x();
            n.x = newPos.y();
            // 移动控件到新位置
            n.button->setGeometry(rect);
        }
        //更新线的位置
        for(int i = 0; i < m_lines.size(); i++){
            m_lines[i].line = QLineF(p2p[m_lines[i].startPoint].button->geometry().center(),p2p[m_lines[i].endPoint].button->geometry().center());
        }
        update();
        //event->accept(); // 阻止事件继续传播
    }
    else{
        QWidget::wheelEvent(event);
    }
}

//鼠标点击
void presentationWidget::mousePressEvent(QMouseEvent* event){
    //记录初始坐标
    oldPos = event->pos();
    Pressed = true;
}

//鼠标移动
void presentationWidget::mouseMoveEvent(QMouseEvent* event){
    if(!Pressed){
        return QWidget::mouseMoveEvent(event);
    }
    this->setCursor(Qt::SizeAllCursor);     //改光标图案
    QPoint pos = event->pos();
    int xMoveInterval = pos.x() - oldPos.x();
    int yMoveInterval = pos.y() - oldPos.y();

    oldPos = pos;

    for(int i = 0; i < p2p.size(); i++){
        p2p[i].button->setGeometry(p2p[i].button->x() + xMoveInterval, p2p[i].button->y() + yMoveInterval, p2p[i].button->width(), p2p[i].button->height());
        //更新位置
        p2p[i].x += xMoveInterval;
        p2p[i].y += yMoveInterval;
    }
    for(int i = 0; i < m_lines.size(); i++){
        m_lines[i].line = QLineF(p2p[m_lines[i].startPoint].button->geometry().center(),p2p[m_lines[i].endPoint].button->geometry().center());
    }
    update();
}
void presentationWidget::mouseReleaseEvent(QMouseEvent* event){
    //鼠标释放函数
    Pressed = false;
    setCursor(Qt::ArrowCursor);
}

void presentationWidget::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    painter.fillRect(rect(), QColor(234, 234, 206)); // 设置背景颜色
    painter.setRenderHint(QPainter::Antialiasing, true);  // 抗锯齿
    // 绘制线段
    for (int i = 0; i < m_lines.size(); i++) {
        const Line& line = m_lines.at(i);
        painter.setPen(QPen(line.color, 8));  // 设置画笔颜色和线宽
        painter.drawLine(line.line);
    }
}

//初始化线
void presentationWidget::addLine(int sp,int ep, const QColor& color)
{
    m_lines.append({ sp,ep,QLineF(p2p[sp].x+40,p2p[sp].y+40,p2p[ep].x+40,p2p[ep].y+40),color});
    update();

}

//删去线
void presentationWidget::removeLine(int node)
{
    for(int i = 0; i < m_lines.size();i++){
        if(m_lines.at(i).startPoint == node || m_lines.at(i).endPoint == node){
            m_lines.remove(i);
            i--;
        }
    }
    //qDebug()<<"lines_size = "<<QString::number(m_lines.size());
    update();
}

bool presentationWidget::deleteNode(int node, ConnectionGraph& graph, vector<Node>& p2p, vector<ClientNode>& clientSet) {
    if (node <= 0 || node >= p2p.size()) {
        return false;
    }
    // 删除连接
    if(!p2p.empty()){
        graph.deleteConnection(node);
        // 删除clientset对应节点
        for (auto it = clientSet.begin(); it != clientSet.end();) {
            // 重置clientnode
            it->reset();
            // 对于要删除节点的后续节点 使其ID减一
            if (it->nodeNum == node) {
                it=clientSet.erase(it);
                while (it != clientSet.end()) {
                    //qDebug()<<"pre_nodeNum  "<<QString::number(it->nodeNum);
                    it->reset();
                    it->nodeNum -= 1;
                    //qDebug()<<"nodeNum  "<<QString::number(it->nodeNum);
                    ++it;
                }
            }
            else {
                ++it;
            }
        }
    }
    if(!p2p.empty()){
        for (auto it = p2p.begin(); it != p2p.end();) {
            if (it->nodeNum == node) {
                //隐藏按钮以及设置文本
                removeLine(node);
                it->button->hide();
                set_ID_text("");
                set_coordinates_text("");
                set_fluency_text("");
                set_data_text("");
                set_delay_text("");
                qDebug()<<"delete:   "<<QString::number(it->nodeNum);
                it = p2p.erase(it);
                while (it != p2p.end()) {
                    it->nodeNum -= 1;
                    ++it;
                }
            }
            else {
                ++it;
            }
        }
    }


    for(int i = 0; i < p2p.size(); i++){
        disconnect(p2p[i].button,&QPushButton::clicked,nullptr,nullptr);
    }
    for(int i = 0; i < m_lines.size(); i++){
        if(m_lines[i].startPoint > node){
            m_lines[i].startPoint--;
        }
        if(m_lines[i].endPoint > node){
            m_lines[i].endPoint--;
        }
    }
//    vector<vector<int>> vertices(p2p.size(), vector<int>(p2p.size(), 0));
//    //初始化连接图类
//    connectionG = ConnectionGraph(vertices, p2p);
//    connectionG.VNconnect();
//    //更新邻接矩阵
//    connectionG.setAdjMatrix();

//    //清空事件队列
//    eventList = priority_queue<Event*, vector< Event*>, cmp>();
//    server.globalDataNum = 0;
//    //模拟事件队列
//    //首先new一个服务器产生事件类并push进事件队列小顶堆eventList中
//    generateEvent = new GenerateVideoBlockEvent(0, server,0,eventList);
//    eventList.push(generateEvent);
//    //接着对每个客户端节点，进行第一次请求事件的初始化并且push进队列
//    for (ClientNode& node : clientSet) {
//        RequestVideoBlockEvent* requestEvent = new RequestVideoBlockEvent(0.1, node.nodeNum - 1, node, clientSet, connectionG.m_connectionList, server,eventList);
//        eventList.push(requestEvent);
//    }
//    double maxTime = 1.9;
//    while (!eventList.empty()) {
//        Event* event = eventList.top();
//        eventList.pop();
//        event->execute();
//        // 超过最大时间则跳出
//        if (event->time > maxTime) {
//            break;
//        }
//        delete event;
//    }
//    while (!eventList.empty()) {
//        Event* event = eventList.top();
//        eventList.pop();
//        delete event;
//    }
//    qDebug()<<"事件队列已清空";
//    //删除线
//    m_lines.clear();
//    //获取连接关系，画线
//    int k = 1;
//    for(int i = 0; i < p2p.size(); i++){
//        for(int j = k; j < p2p.size(); j++){
//            if(connectionG.m_vertices[i][j] == 1){
//                addLine(i,j,Qt::green);
//            }
//        }
//        k++;
//    }
//    for(int i = 0; i < m_lines.size(); i++){
//        m_lines[i].line = QLineF(p2p[m_lines[i].startPoint].button->geometry().center(),p2p[m_lines[i].endPoint].button->geometry().center());
//    }

//    for(int i = 0; i < p2p.size();i++){
//        connect(p2p[i].button, &QPushButton::clicked, this, [=]() {
//            if(p2p[i].nodeNum != lastChoose){
//                //相邻条件
//                for(int j = 0; j < m_lines.size(); j++){
//                    if(m_lines[j].startPoint == p2p[i].nodeNum || m_lines[j].endPoint == p2p[i].nodeNum){
//                        m_lines[j].color = Qt::blue;
//                        continue;
//                    }
//                    if(m_lines[j].startPoint == lastChoose || m_lines[j].endPoint == lastChoose){
//                        m_lines[j].color = Qt::green;
//                    }
//                }
//                lastChoose = p2p[i].nodeNum;
//                update();
//            }
//            else{
//                //取消选中
//                for(int j = 0; j < m_lines.size(); j++){
//                    if(m_lines[j].startPoint == lastChoose || m_lines[j].endPoint == lastChoose){
//                        m_lines[j].color = Qt::green;
//                    }
//                }
//                lastChoose = -1;
//                update();
//            }
//        });

//        connect(p2p[i].button, &QPushButton::clicked,this,[=](){
//            if(lastChoose != -1){
//                qDebug()<<"idtext"<<QString::number(p2p[i].nodeNum);
//                set_ID_text(QString::number(p2p[i].nodeNum));
//                set_coordinates_text("( " + QString::number(p2p[i].x) + " , " + QString::number(p2p[i].y) + " ) ");
//                if(i > 0){
//                    QString str1,str2;
//                    vector<pair<int, double>> memory = clientSet[i-1].playTimeMemory;
//                    for(int j = 0;j < clientSet[i-1].dataBuffer.size() && j < 5;j++){
//                        str1 += QString::number(clientSet[i-1].dataBuffer[j].dataNum)+'\n';
//                        //if(clientSet[i-1].dataBuffer[j].dataNum < memory.size())
//                            //str2 += QString::number(memory[clientSet[i-1].dataBuffer[j].dataNum].second - (memory[clientSet[i-1].dataBuffer[j].dataNum].first / 31)) + '\n';
//                        str2 += QString::number(clientSet[i-1].playTimeMemory[j].first)+"  " + QString::number(clientSet[i-1].playTimeMemory[j].second - (clientSet[i-1].playTimeMemory[j].first / 31))  + '\n';

//                        //else
//                        //    str2 += '\n';
//                        //qDebug() << "数据块编号：" << memory[i].first << "播放时间：" << memory[i].second << "播放延迟：" << memory[i].second - (memory[i].first / 31) << endl;
//                    }
//                    for(int j = 0;j < clientSet[i-1].playTimeMemory.size();j++){
//                        qDebug()<<QString::number(clientSet[i-1].playTimeMemory[j].first)+"  " + QString::number(clientSet[i-1].playTimeMemory[j].second) + " " + QString::number((clientSet[i-1].playTimeMemory[j].first / 31)) +  " " + QString::number(clientSet[i-1].playTimeMemory[j].second - (clientSet[i-1].playTimeMemory[j].first / 31));
//                    }
//                    send_information(lastChoose,clientSet[i-1].dataBuffer,memory);
//                    set_data_text(str1);
//                    set_delay_text(str2);
//                    set_fluency_text(QString::number(clientSet[i-1].contiousPlayTime / clientSet[i-1].endPlayTime));
//                }
//            }
//            else{
//                set_ID_text("");
//                set_coordinates_text("");
//                set_data_text("");
//                set_fluency_text("");
//                set_delay_text("");
//            }
//            //qDebug()<<QString::number(p2p.size())<<"number:";
// //            for(auto iter: p2p){
// //                qDebug()<<QString::number(iter.nodeNum);
// //            }
//        });
//    }
//    lastChoose = -1;
//    qDebug()<<"deleteNode完成";
    return true;
}

//设置ID文本
void presentationWidget::set_ID_text(QString str)
{
    // 在槽函数中通过父指针访问W类，完成对Label文本的设置
    Total *w = qobject_cast<Total *>(parent());
    if (w) {
        w->setidLabelText(str);
    }
}

//设置坐标文本
void presentationWidget::set_coordinates_text(QString str)
{
    // 在槽函数中通过父指针访问W类，完成对Label文本的设置
    Total *w = qobject_cast<Total *>(parent());
    if (w) {
        w->setcoordinatesLabelText(str);
    }

}

//设置数据块文本
void presentationWidget::set_data_text(QString str)
{
    // 在槽函数中通过父指针访问W类，完成对Label文本的设置
    Total *w = qobject_cast<Total *>(parent());
    if (w) {
        w->setdataLabelText(str);
    }

}

//设置流畅度文本
void presentationWidget::set_fluency_text(QString str)
{
    // 在槽函数中通过父指针访问W类，完成对Label文本的设置
    Total *w = qobject_cast<Total *>(parent());
    if (w) {
        w->setfluencyLabelText(str);
    }

}
//设置延迟文本
void presentationWidget::set_delay_text(QString str)
{
    // 在槽函数中通过父指针访问W类，完成对Label文本的设置
    Total *w = qobject_cast<Total *>(parent());
    if (w) {
        w->setdelayLabelText(str);
    }

}
void presentationWidget::send_information(int lc,vector<DataBlock> block,vector<pair<int, double>> memory){
    Total *w = qobject_cast<Total *>(parent());
    w->cur_block = block;
    w->cur_memory = memory;
    w->choose = lc;
}
//开始事件
void presentationWidget::startEvent(){
    vector<vector<int>> vertices(listSize, vector<int>(listSize, 0));
    //初始化连接图类
    connectionG = ConnectionGraph(vertices, p2p);
    connectionG.VNconnect();
    //更新邻接矩阵
    connectionG.setAdjMatrix();
    //清空事件队列
        eventList = priority_queue<Event*, vector< Event*>, cmp>();
        server.globalDataNum = 0;
    for (auto it = clientSet.begin(); it != clientSet.end();) {
        // 重置clientnode
        it->reset();
        it++;
    }

    //获取连接关系，画线
    int k = 1;
    for(int i = 0; i < listSize; i++){
        for(int j = k; j < listSize; j++){
            if(connectionG.m_vertices[i][j] == 1){
                addLine(i,j,Qt::green);
            }
        }
        k++;
    }

    for(int i = 0; i < m_lines.size(); i++){
        m_lines[i].line = QLineF(p2p[m_lines[i].startPoint].button->geometry().center(),p2p[m_lines[i].endPoint].button->geometry().center());
    }

    p2p[0].button->setStyleSheet("background:transparent;border-image: url(:/server_1.png);");
    for(int i = 0; i < p2p.size();i++){
        connect(p2p[i].button, &QPushButton::clicked, this, [=]() {
            if(p2p[i].nodeNum != lastChoose){
                //相邻条件
                for(int j = 0; j < m_lines.size(); j++){
                    if(m_lines[j].startPoint == p2p[i].nodeNum || m_lines[j].endPoint == p2p[i].nodeNum){
                        m_lines[j].color = Qt::blue;
                        continue;
                    }
                    if(m_lines[j].startPoint == lastChoose || m_lines[j].endPoint == lastChoose){
                        m_lines[j].color = Qt::green;
                    }
                }
                lastChoose = p2p[i].nodeNum;
                update();
            }
            else{
                //取消选中
                for(int j = 0; j < m_lines.size(); j++){
                    if(m_lines[j].startPoint == lastChoose || m_lines[j].endPoint == lastChoose){
                        m_lines[j].color = Qt::green;
                    }
                }
                lastChoose = -1;
                update();
            }
        });
        connect(p2p[i].button, &QPushButton::clicked,this,[=](){
            if(lastChoose != -1){
                qDebug()<<"idtext"<<QString::number(p2p[i].nodeNum);
                set_ID_text(QString::number(p2p[i].nodeNum));
                set_coordinates_text("( " + QString::number(p2p[i].x) + " , " + QString::number(p2p[i].y) + " ) ");
                if(i > 0){
                    QString str1,str2;
                    vector<pair<int, double>> memory = clientSet[i-1].playTimeMemory;
                    for(int j = 0;j < clientSet[i-1].dataBuffer.size() && j < 5;j++){
                        str1 += QString::number(clientSet[i-1].dataBuffer[j].dataNum)+'\n';
                        str2 += QString::number(clientSet[i-1].playTimeMemory[j].first)+" : " + QString::number(clientSet[i-1].playTimeMemory[j].second - (clientSet[i-1].playTimeMemory[j].first / 31))  + '\n';
                    }
                    set_data_text(str1);
                    set_delay_text(str2);
                    set_fluency_text(QString::number(clientSet[i-1].contiousPlayTime / clientSet[i-1].endPlayTime));
                    send_information(lastChoose,clientSet[i-1].dataBuffer,memory);
                }
            }
            else{
                set_ID_text("");
                set_coordinates_text("");
                set_data_text("");
                set_fluency_text("");
                set_delay_text("");
            }
            qDebug()<<QString::number(p2p.size())<<"number:";
//            for(auto iter: p2p){
//                qDebug()<<QString::number(iter.nodeNum);
//            }
        });
    }

    //模拟事件队列
    //首先new一个服务器产生事件类并push进事件队列小顶堆eventList中
    generateEvent = new GenerateVideoBlockEvent(0, server,0,eventList);
    eventList.push(generateEvent);
    //接着对每个客户端节点，进行第一次请求事件的初始化并且push进队列
    for (ClientNode& node : clientSet) {
        RequestVideoBlockEvent* requestEvent = new RequestVideoBlockEvent(0.1, node.nodeNum - 1, node, clientSet, connectionG.m_connectionList, server,eventList);
        eventList.push(requestEvent);
    }
    double maxTime = 1.9;
    while (!eventList.empty()) {
        Event* event = eventList.top();
        eventList.pop();
        event->execute();
        // 超过最大时间则跳出
        if (event->time > maxTime) {
            break;
        }
        delete event;
    }
    while (!eventList.empty()) {
        Event* event = eventList.top();
        eventList.pop();
        delete event;
    }
    // 测试流畅度
    for (int i = 0; i < clientSet.size(); i++) {
        qDebug() << clientSet[i].contiousPlayTime;

        qDebug() <<QString::number(i) << "号客户端，流畅度为：" <<QString::number(clientSet[i].contiousPlayTime/ clientSet[i].endPlayTime);
    }
    // 测试播放延迟，以零号客户端为例
    vector<pair<int, double>> memory = clientSet[0].playTimeMemory;
    for (int i = 0; i < memory.size(); i++) {
        qDebug() << "数据块编号：" <<QString::number(memory[i].first)<< "播放时间：" << QString::number(memory[i].second) << "播放延迟：" << QString::number(memory[i].second - (memory[i].first / 31));
    }
}

void presentationWidget::stepEvent_first(){
    vector<vector<int>> vertices(listSize, vector<int>(listSize, 0));
    //初始化连接图类
    connectionG = ConnectionGraph(vertices, p2p);
    connectionG.VNconnect();
    //更新邻接矩阵
    connectionG.setAdjMatrix();

    //获取连接关系，画线
    int k = 1;
    for(int i = 0; i < listSize; i++){
        for(int j = k; j < listSize; j++){
            if(connectionG.m_vertices[i][j] == 1){
                addLine(i,j,Qt::green);
            }
        }
        k++;
    }

    for(int i = 0; i < m_lines.size(); i++){
        m_lines[i].line = QLineF(p2p[m_lines[i].startPoint].button->geometry().center(),p2p[m_lines[i].endPoint].button->geometry().center());
    }

    p2p[0].button->setStyleSheet("background:transparent;border-image: url(:/server_1.png);");
    for(int i = 0; i < p2p.size();i++){
        connect(p2p[i].button, &QPushButton::clicked, this, [=]() {
            if(p2p[i].nodeNum != lastChoose){
                //相邻条件
                for(int j = 0; j < m_lines.size(); j++){
                    if(m_lines[j].startPoint == p2p[i].nodeNum || m_lines[j].endPoint == p2p[i].nodeNum){
                        m_lines[j].color = Qt::blue;
                        continue;
                    }
                    if(m_lines[j].startPoint == lastChoose || m_lines[j].endPoint == lastChoose){
                        m_lines[j].color = Qt::green;
                    }
                }
                lastChoose = p2p[i].nodeNum;
                update();
            }
            else{
                //取消选中
                for(int j = 0; j < m_lines.size(); j++){
                    if(m_lines[j].startPoint == lastChoose || m_lines[j].endPoint == lastChoose){
                        m_lines[j].color = Qt::green;
                    }
                }
                lastChoose = -1;
                update();
            }
        });
        connect(p2p[i].button, &QPushButton::clicked,this,[=](){
            if(lastChoose != -1){
                qDebug()<<"idtext"<<QString::number(p2p[i].nodeNum);
                set_ID_text(QString::number(p2p[i].nodeNum));
                set_coordinates_text("( " + QString::number(p2p[i].x) + " , " + QString::number(p2p[i].y) + " ) ");
                if(i > 0){
                    QString str1,str2;
                    vector<pair<int, double>> memory = clientSet[i-1].playTimeMemory;
                    for(int j = 0;j < clientSet[i-1].dataBuffer.size() && j < 5;j++){
                        str1 += QString::number(clientSet[i-1].dataBuffer[j].dataNum)+'\n';
                        str2 += QString::number(clientSet[i-1].playTimeMemory[j].first)+" : " + QString::number(clientSet[i-1].playTimeMemory[j].second - (clientSet[i-1].playTimeMemory[j].first / 31))  + '\n';
                    }
                    set_data_text(str1);
                    set_delay_text(str2);
                    set_fluency_text(QString::number(clientSet[i-1].contiousPlayTime / clientSet[i-1].endPlayTime));
                    send_information(lastChoose,clientSet[i-1].dataBuffer,memory);
                }
            }
            else{
                set_ID_text("");
                set_coordinates_text("");
                set_data_text("");
                set_fluency_text("");
                set_delay_text("");
            }
            qDebug()<<QString::number(p2p.size())<<"number:";
            //            for(auto iter: p2p){
            //                qDebug()<<QString::number(iter.nodeNum);
            //            }
        });
    }

    //模拟事件队列
    //首先new一个服务器产生事件类并push进事件队列小顶堆eventList中
    generateEvent = new GenerateVideoBlockEvent(0, server,0,eventList);
    eventList.push(generateEvent);
    //接着对每个客户端节点，进行第一次请求事件的初始化并且push进队列
    for (ClientNode& node : clientSet) {
        RequestVideoBlockEvent* requestEvent = new RequestVideoBlockEvent(0.1, node.nodeNum - 1, node, clientSet, connectionG.m_connectionList, server,eventList);
        eventList.push(requestEvent);
    }
}

void presentationWidget::stepEvent(){
    if(!eventList.empty()){
        Event* event = eventList.top();
        eventList.pop();
        event->execute();
        delete event;
        if(lastChoose > 0){
            QString str1,str2;
            vector<pair<int, double>> memory = clientSet[lastChoose-1].playTimeMemory;
            for(int j = 0;j < clientSet[lastChoose-1].dataBuffer.size() && j < 5;j++){
                str1 += QString::number(clientSet[lastChoose-1].dataBuffer[j].dataNum)+'\n';
                str2 += QString::number(clientSet[lastChoose-1].playTimeMemory[j].first)+" : " + QString::number(clientSet[lastChoose-1].playTimeMemory[j].second - (clientSet[lastChoose-1].playTimeMemory[j].first / 31))  + '\n';
            }
            set_data_text(str1);
            set_delay_text(str2);
            set_fluency_text(QString::number(clientSet[lastChoose-1].contiousPlayTime / clientSet[lastChoose-1].endPlayTime));
            send_information(lastChoose,clientSet[lastChoose-1].dataBuffer,memory);
        }
    }
}

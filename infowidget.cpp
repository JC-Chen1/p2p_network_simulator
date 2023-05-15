#include "infowidget.h"
#include "ui_infowidget.h"
#include<QScrollArea>
#include<QVBoxLayout>
InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    setWindowFlags(Qt::FramelessWindowHint);//窗口仅用于输出，不接收任何输入事件
    ui->scrollArea->setStyleSheet(
        "QScrollBar:vertical{width:8px;background:transparent;margin:0px,1px,0px,1px;"
        "padding-top:0px;padding-bottom:0px;border-radius:4px;}"
        "QScrollBar::handle:vertical{background:rgb(213, 213, 213,0.8);border-radius:4px;}"
        "QScrollBar::handle:vertical:hover{background:rgb(180, 180, 180,0.8);border-radius:4px;}"
        "QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{background:transparent;border-radius:4px;}"
        "QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{height:0px;width:0px;}"
        );

    connect(ui->pushButton,&QPushButton::clicked,[=](){
        this->close();
    });

}

InfoWidget::~InfoWidget()
{
    delete ui;
}

void InfoWidget::setInfo(int choose,vector<DataBlock> cur_block,vector<pair<int, double>> cur_memory){
    ui->label_cid->setText(QString::number(choose));
    QString str1,str2;
    for(int i = 0; i < cur_block.size(); i++){
        str1 += QString::number(cur_block[i].dataNum) + '\n';
    }
    for(int i = 0; i < cur_memory.size(); i++){
        str2 += QString::number(cur_memory[i].first)+"  :  " + QString::number(cur_memory[i].second - (cur_memory[i].first/31))  + '\n';
    }
    ui->label_bn->setText(str1);
    ui->label_delay->setText(str2);
    //动态适应文字大小
    ui->label_bn->adjustSize();
    ui->label_delay->adjustSize();
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollAreaWidgetContents->setGeometry(0,0,929,ui->label_delay->size().height()+200);
}

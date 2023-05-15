#include "infowidget.h"
#include "ui_infowidget.h"
#include<QScrollArea>
#include<QVBoxLayout>
InfoWidget::InfoWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::InfoWidget)
{
    ui->setupUi(this);


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
        str2 += QString::number(cur_memory[i].first)+"  :  " + QString::number(cur_memory[i].second)  + '\n';
    }
    ui->label_bn->setText(str1);
    ui->label_delay->setText(str2);

}

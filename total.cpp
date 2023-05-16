#include "total.h"
#include "ui_infowidget.h"
#include "ui_total.h"
#include"intro.h"


Total::Total(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Total)
{
    ui->setupUi(this);
    started = false;
    stepTimes = 0;
    presentationWidget* p = new presentationWidget(this);
    prew = p;
    prew->setGeometry(320,60,980,780);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    ui->pushButton_start->setIcon(QIcon(":/start.png"));
    ui->pushButton_start->setIconSize(QSize(28,28));
    ui->pushButton_step->setIcon(QIcon(":/step.png"));
    ui->pushButton_step->setIconSize(QSize(28,28));
    ui->pushButton_delete->setIcon(QIcon(":/delete.png"));
    ui->pushButton_delete->setIconSize(QSize(28,28));

}

Total::~Total()
{
    delete ui;
}

void Total::on_pushButton_clicked()
{
    this->close();
}

void Total::paintEvent(QPaintEvent *event)
{
    setAutoFillBackground(false);
    setPalette(QPalette(Qt::transparent));
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); // 抗锯齿
    painter.setBrush(QColor(255, 255, 255, 0)); // 设置填充颜色为透明
    painter.setPen(Qt::NoPen); // 设置画笔为无
    painter.drawRoundedRect(rect(), 10, 10); // 绘制圆角矩形
}

void Total::on_pushButton_delete_clicked()
{
    //prew->deleteCustomer(prew->lastChoose);
    prew->deleteNode(prew->lastChoose,prew->connectionG,prew->p2p,prew->clientSet);
    started = false;
    stepTimes = 0;
    ui->pushButton_start->setEnabled(true);
    ui->pushButton_step->setEnabled(true);
    ui->lineEdit->setText(QString::number(prew->clientSet.size()));
}
void Total::setidLabelText(const QString &text)
{
    ui->label_id->setText(text);
}

void Total::setcoordinatesLabelText(const QString &text)
{
    ui->label_Coordinates->setText(text);
}

void Total::on_pushButton_shrink_clicked()
{
    this->showMinimized();
}

void Total::setdataLabelText(const QString &text){
    ui->label_data->setText(text);
}

void Total::setfluencyLabelText(const QString &text){
    ui->label_flu->setText(text);
}
void Total::setdelayLabelText(const QString &text){
    ui->label_fluency->setText(text);
}

void Total::on_pushButton_more_clicked()
{
    if(prew->lastChoose > 0){
        InfoWidget* w = new InfoWidget();
        w->setInfo(prew->lastChoose,cur_block,cur_memory);
        w->show();
    }
}


void Total::on_pushButton_start_clicked()
{
    if(prew->listSize > 0){
        if(!started){
            prew->startEvent();
            started = true;
        }
        ui->pushButton_start->setEnabled(false);
        ui->pushButton_step->setEnabled(false);
    }
}


void Total::on_pushButton_step_clicked()
{
    if(prew->listSize > 0){
        if(stepTimes == 0){
            prew->stepEvent_first();
            stepTimes++;
        }
        else{
            prew->stepEvent();
            stepTimes++;
        }
        ui->pushButton_start->setEnabled(false);
    }
}

//开始生成
void Total::on_pushButton_generate_clicked()
{
    int k = (ui->lineEdit->text()).toInt();
    prew->generate(k);
    ui->pushButton_generate->setEnabled(false);
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->setText(QString::number(k-1));
    ui->label_3->setText("Number of current clients:");
}


void Total::on_pushButton_2_clicked()
{
    Intro* intro = new Intro;
    intro->show();
}


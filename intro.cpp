#include "intro.h"
#include "ui_intro.h"

Intro::Intro(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Intro)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    setWindowFlags(Qt::FramelessWindowHint);//窗口仅用于输出，不接收任何输入事件
}

Intro::~Intro()
{
    delete ui;
}

void Intro::on_pushButton_clicked()
{
    this->close();
}


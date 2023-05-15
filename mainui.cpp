#include "mainui.h"
#include "ui_mainui.h"


mainUI::mainUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainUI)
{
    ui->setupUi(this);
}

mainUI::~mainUI()
{
    delete ui;
}

void mainUI::wheelEvent(QWheelEvent *event){

    int x = QCursor().pos().x();    // 获取当前鼠标滚轮位置x
    int y = QCursor().pos().y();    // 获取当前鼠标滚轮位置y
}

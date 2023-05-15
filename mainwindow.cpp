
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "total.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //设置窗口为圆角必须设置背景透明和无边框
    setAttribute(Qt::WA_TranslucentBackground);//设置背景透明
    setWindowFlags(Qt::FramelessWindowHint);//窗口仅用于输出，不接收任何输入事件
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    Total* preWidget = new Total;
    preWidget->show();
    this->close();
}


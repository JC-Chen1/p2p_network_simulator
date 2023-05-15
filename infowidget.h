#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include <QWidget>
#include "datablock.h"
#include<vector>
#include<iostream>

namespace Ui {
class InfoWidget;
}
using namespace std;
class InfoWidget : public QWidget
{
    Q_OBJECT

public:
    explicit InfoWidget(QWidget *parent = nullptr);
    ~InfoWidget();
    void setInfo(int choose,vector<DataBlock> cur_block,vector<pair<int, double>> cur_memory);
    Ui::InfoWidget *ui;

private:

};

#endif // INFOWIDGET_H

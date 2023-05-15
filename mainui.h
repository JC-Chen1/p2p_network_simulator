#ifndef MAINUI_H
#define MAINUI_H

#include <QWidget>
#include<QWheelEvent>
#include<QPoint>
#include<QDebug>


namespace Ui {
class mainUI;
}

class mainUI : public QWidget
{
    Q_OBJECT

public:
    explicit mainUI(QWidget *parent = nullptr);
    ~mainUI();
    void wheelEvent(QWheelEvent* event);

private:
    Ui::mainUI *ui;
};

#endif // MAINUI_H

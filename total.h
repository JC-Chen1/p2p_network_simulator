#ifndef TOTAL_H
#define TOTAL_H

#include <QWidget>
#include<QPaintEvent>
#include<QMouseEvent>
#include"presentationwidget.h"
#include"infowidget.h"

namespace Ui {
class Total;
}

class Total : public QWidget
{
    Q_OBJECT

public:
    explicit Total(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

    presentationWidget* prew;
    vector<DataBlock> cur_block;
    vector<pair<int, double>> cur_memory;
    int stepTimes;
    bool started;
    ~Total();
public slots:
    void setidLabelText(const QString &text);
    void setcoordinatesLabelText(const QString &text);
    void setdataLabelText(const QString &text);
    void setfluencyLabelText(const QString &text);
    void setdelayLabelText(const QString &text);

private slots:
    void on_pushButton_clicked(); 
    void on_pushButton_delete_clicked();
    void on_pushButton_shrink_clicked();
    void on_pushButton_more_clicked();
    void on_pushButton_start_clicked();
    void on_pushButton_step_clicked();
    void on_pushButton_generate_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Total *ui;
    QPoint m_dragPos;
};

#endif // TOTAL_H

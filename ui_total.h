/********************************************************************************
** Form generated from reading UI file 'total.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOTAL_H
#define UI_TOTAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Total
{
public:
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *pushButton_start;
    QPushButton *pushButton_delete;
    QPushButton *pushButton_step;
    QLabel *label_id_t;
    QLabel *label_id;
    QLabel *label_data_t;
    QLabel *label_data;
    QPushButton *pushButton_shrink;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QFrame *frame_bar;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QPushButton *pushButton_generate;
    QFrame *frame_2;
    QFrame *frame_3;
    QLabel *label_Coordinates_t;
    QLabel *label_Coordinates;
    QLabel *label_fluency_t;
    QLabel *label_fluency;
    QPushButton *pushButton_more;
    QLabel *label_flu_t;
    QLabel *label_flu;

    void setupUi(QWidget *Total)
    {
        if (Total->objectName().isEmpty())
            Total->setObjectName("Total");
        Total->resize(1338, 830);
        Total->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(Total);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 10, 1338, 830));
        frame->setStyleSheet(QString::fromUtf8("#frame{\n"
"	background-color: rgba(240, 240, 240,0.87);\n"
"	border-radius: 35px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(30, 30, 20, 20));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/red.png);"));
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName("pushButton_start");
        pushButton_start->setGeometry(QRect(30, 110, 231, 41));
        pushButton_start->setLayoutDirection(Qt::LeftToRight);
        pushButton_start->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font: 500 18pt \"Century Gothic\";\n"
"	background:transparent;\n"
"        color: rgb(65, 65, 65);  \n"
"        border-radius: 9px;  \n"
"        border-style: outset;\n"
"		border: none;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	   color: black;   \n"
"        border-radius: 9px; \n"
"        border-style: outset;\n"
"		border: none;\n"
"		background: rgba(163, 163, 163,0.7);\n"
"}"));
        pushButton_delete = new QPushButton(frame);
        pushButton_delete->setObjectName("pushButton_delete");
        pushButton_delete->setGeometry(QRect(30, 160, 231, 41));
        pushButton_delete->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font: 500 18pt \"Century Gothic\";\n"
"	background:transparent;\n"
"        color: rgb(65, 65, 65);  \n"
"        border-radius: 9px;  \n"
"        border-style: outset;\n"
"		border: none;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	   color: black;   \n"
"        border-radius: 9px; \n"
"        border-style: outset;\n"
"		border: none;\n"
"		background: rgba(163, 163, 163,0.7);\n"
"}"));
        pushButton_step = new QPushButton(frame);
        pushButton_step->setObjectName("pushButton_step");
        pushButton_step->setGeometry(QRect(30, 210, 231, 41));
        pushButton_step->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font: 500 18pt \"Century Gothic\";\n"
"	background:transparent;\n"
"        color: rgb(65, 65, 65);  \n"
"        border-radius: 9px;  \n"
"        border-style: outset;\n"
"		border: none;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	   color: black;   \n"
"        border-radius: 9px; \n"
"        border-style: outset;\n"
"		border: none;\n"
"		background: rgba(163, 163, 163,0.7);\n"
"}"));
        label_id_t = new QLabel(frame);
        label_id_t->setObjectName("label_id_t");
        label_id_t->setGeometry(QRect(20, 320, 81, 31));
        label_id_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_id_t->setAlignment(Qt::AlignCenter);
        label_id = new QLabel(frame);
        label_id->setObjectName("label_id");
        label_id->setGeometry(QRect(140, 320, 111, 31));
        label_id->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_data_t = new QLabel(frame);
        label_data_t->setObjectName("label_data_t");
        label_data_t->setGeometry(QRect(50, 510, 51, 31));
        label_data_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_data_t->setAlignment(Qt::AlignCenter);
        label_data = new QLabel(frame);
        label_data->setObjectName("label_data");
        label_data->setGeometry(QRect(40, 550, 81, 191));
        label_data->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_data->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pushButton_shrink = new QPushButton(frame);
        pushButton_shrink->setObjectName("pushButton_shrink");
        pushButton_shrink->setGeometry(QRect(60, 30, 21, 21));
        pushButton_shrink->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/shrink.png);"));
        pushButton_2 = new QPushButton(frame);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(90, 27, 27, 27));
        pushButton_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0);\n"
"border-image: url(:/about.png);"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(20, 80, 101, 21));
        label->setStyleSheet(QString::fromUtf8("font: 12pt \"Century Gothic\";\n"
"background:transparent;"));
        label_2 = new QLabel(frame);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(20, 280, 111, 21));
        label_2->setStyleSheet(QString::fromUtf8("font: 12pt \"Century Gothic\";\n"
"background:transparent;"));
        frame_bar = new QFrame(frame);
        frame_bar->setObjectName("frame_bar");
        frame_bar->setGeometry(QRect(280, 0, 1057, 51));
        frame_bar->setStyleSheet(QString::fromUtf8("background-color: rgba(226, 226, 226,0.9);\n"
"border:1px solid rgb(216, 216, 216);\n"
"border-top-right-radius:35px;"));
        frame_bar->setFrameShape(QFrame::Box);
        frame_bar->setFrameShadow(QFrame::Plain);
        frame_bar->setLineWidth(1);
        lineEdit = new QLineEdit(frame_bar);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(360, 10, 111, 31));
        lineEdit->setStyleSheet(QString::fromUtf8("border: none;\n"
"border-bottom: 1px solid black;\n"
"font: 700 14pt \"Adobe Caslon Pro Bold\";\n"
"color: rgb(0, 85, 0);"));
        lineEdit->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_3 = new QLabel(frame_bar);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(20, 10, 321, 41));
        label_3->setStyleSheet(QString::fromUtf8("QLabel{font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;border: none;\n"
"border-radius:0px}"));
        label_3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        pushButton_generate = new QPushButton(frame_bar);
        pushButton_generate->setObjectName("pushButton_generate");
        pushButton_generate->setGeometry(QRect(490, 10, 131, 31));
        pushButton_generate->setStyleSheet(QString::fromUtf8("QPushButton\n"
"{\n"
"	font: 500 15pt \"Century Gothic\";\n"
"	background: rgba(163, 163, 163,0.7);\n"
"        color: rgb(65, 65, 65);  \n"
"        border-radius: 9px;  \n"
"        border-style: outset;\n"
"		border: none;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"	   color: black;   \n"
"        border-radius: 9px; \n"
"        border-style: outset;\n"
"		border: none;\n"
"		background: rgba(163, 163, 163,0.7);\n"
"}\n"
""));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName("frame_2");
        frame_2->setGeometry(QRect(280, 49, 40, 811));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid rgb(216, 216, 216);"));
        frame_2->setFrameShape(QFrame::Box);
        frame_2->setFrameShadow(QFrame::Plain);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName("frame_3");
        frame_3->setGeometry(QRect(1300, 50, 38, 781));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"border:1px solid rgb(216, 216, 216);\n"
"border-bottom-right-radius:35px;"));
        frame_3->setFrameShape(QFrame::Box);
        frame_3->setFrameShadow(QFrame::Sunken);
        label_Coordinates_t = new QLabel(frame);
        label_Coordinates_t->setObjectName("label_Coordinates_t");
        label_Coordinates_t->setGeometry(QRect(40, 360, 121, 31));
        label_Coordinates_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_Coordinates_t->setAlignment(Qt::AlignCenter);
        label_Coordinates = new QLabel(frame);
        label_Coordinates->setObjectName("label_Coordinates");
        label_Coordinates->setGeometry(QRect(50, 400, 171, 41));
        label_Coordinates->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_fluency_t = new QLabel(frame);
        label_fluency_t->setObjectName("label_fluency_t");
        label_fluency_t->setGeometry(QRect(120, 510, 121, 31));
        label_fluency_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_fluency_t->setAlignment(Qt::AlignCenter);
        label_fluency = new QLabel(frame);
        label_fluency->setObjectName("label_fluency");
        label_fluency->setGeometry(QRect(110, 550, 161, 221));
        label_fluency->setStyleSheet(QString::fromUtf8("font: 700 14pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_fluency->setAlignment(Qt::AlignHCenter|Qt::AlignTop);
        pushButton_more = new QPushButton(frame);
        pushButton_more->setObjectName("pushButton_more");
        pushButton_more->setGeometry(QRect(120, 780, 31, 31));
        pushButton_more->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"border-image: url(:/more1.png);"));
        label_flu_t = new QLabel(frame);
        label_flu_t->setObjectName("label_flu_t");
        label_flu_t->setGeometry(QRect(40, 450, 91, 31));
        label_flu_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_flu_t->setAlignment(Qt::AlignCenter);
        label_flu = new QLabel(frame);
        label_flu->setObjectName("label_flu");
        label_flu->setGeometry(QRect(150, 450, 101, 31));
        label_flu->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_flu->setAlignment(Qt::AlignCenter);

        retranslateUi(Total);

        QMetaObject::connectSlotsByName(Total);
    } // setupUi

    void retranslateUi(QWidget *Total)
    {
        Total->setWindowTitle(QCoreApplication::translate("Total", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_start->setText(QCoreApplication::translate("Total", "      Start     ", nullptr));
        pushButton_delete->setText(QCoreApplication::translate("Total", "    Delete   ", nullptr));
        pushButton_step->setText(QCoreApplication::translate("Total", "      Step    ", nullptr));
        label_id_t->setText(QCoreApplication::translate("Total", "ID:", nullptr));
        label_id->setText(QString());
        label_data_t->setText(QCoreApplication::translate("Total", "Data", nullptr));
        label_data->setText(QString());
        pushButton_shrink->setText(QString());
        pushButton_2->setText(QString());
        label->setText(QCoreApplication::translate("Total", "Function:", nullptr));
        label_2->setText(QCoreApplication::translate("Total", "Infomation:", nullptr));
        lineEdit->setText(QString());
        label_3->setText(QCoreApplication::translate("Total", "Please enter the number of nodes\357\274\232", nullptr));
#if QT_CONFIG(whatsthis)
        pushButton_generate->setWhatsThis(QCoreApplication::translate("Total", "<html><head/><body><p>generate now</p></body></html>", nullptr));
#endif // QT_CONFIG(whatsthis)
        pushButton_generate->setText(QCoreApplication::translate("Total", "generate", nullptr));
        label_Coordinates_t->setText(QCoreApplication::translate("Total", "Coordinates:", nullptr));
        label_Coordinates->setText(QString());
        label_fluency_t->setText(QCoreApplication::translate("Total", "id&Delay", nullptr));
        label_fluency->setText(QString());
        pushButton_more->setText(QString());
        label_flu_t->setText(QCoreApplication::translate("Total", "Fluency:", nullptr));
        label_flu->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Total: public Ui_Total {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOTAL_H

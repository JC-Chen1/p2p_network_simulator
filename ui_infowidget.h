/********************************************************************************
** Form generated from reading UI file 'infowidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INFOWIDGET_H
#define UI_INFOWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InfoWidget
{
public:
    QFrame *frame;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QLabel *label_delay;
    QLabel *label_bn_t;
    QLabel *label_delay_t;
    QLabel *label_bn;
    QPushButton *pushButton;
    QLabel *label_cid_t;
    QLabel *label_cid;

    void setupUi(QWidget *InfoWidget)
    {
        if (InfoWidget->objectName().isEmpty())
            InfoWidget->setObjectName("InfoWidget");
        InfoWidget->resize(928, 793);
        frame = new QFrame(InfoWidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(0, 0, 928, 793));
        frame->setStyleSheet(QString::fromUtf8("QFrame{\n"
"border-radius:30px;\n"
"background-color: rgb(255, 255, 255);\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        scrollArea = new QScrollArea(frame);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setGeometry(QRect(10, 80, 910, 691));
        scrollArea->setStyleSheet(QString::fromUtf8("background:transparent;"));
        scrollArea->setWidgetResizable(false);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 929, 3000));
        label_delay = new QLabel(scrollAreaWidgetContents);
        label_delay->setObjectName("label_delay");
        label_delay->setGeometry(QRect(480, 90, 251, 3000));
        label_delay->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_delay->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_bn_t = new QLabel(scrollAreaWidgetContents);
        label_bn_t->setObjectName("label_bn_t");
        label_bn_t->setGeometry(QRect(30, 30, 151, 31));
        label_bn_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_delay_t = new QLabel(scrollAreaWidgetContents);
        label_delay_t->setObjectName("label_delay_t");
        label_delay_t->setGeometry(QRect(500, 30, 181, 31));
        label_delay_t->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_bn = new QLabel(scrollAreaWidgetContents);
        label_bn->setObjectName("label_bn");
        label_bn->setGeometry(QRect(50, 99, 151, 3001));
        label_bn->setStyleSheet(QString::fromUtf8("font: 700 16pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;"));
        label_bn->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(850, 20, 41, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"border-image: url(:/close.png);"));
        label_cid_t = new QLabel(frame);
        label_cid_t->setObjectName("label_cid_t");
        label_cid_t->setGeometry(QRect(40, 40, 151, 31));
        label_cid_t->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;\n"
"color: rgb(0, 85, 0);"));
        label_cid = new QLabel(frame);
        label_cid->setObjectName("label_cid");
        label_cid->setGeometry(QRect(210, 40, 151, 31));
        label_cid->setStyleSheet(QString::fromUtf8("font: 700 20pt \"Adobe Caslon Pro Bold\";\n"
"background:transparent;\n"
"color: rgb(0, 85, 0);"));

        retranslateUi(InfoWidget);

        QMetaObject::connectSlotsByName(InfoWidget);
    } // setupUi

    void retranslateUi(QWidget *InfoWidget)
    {
        InfoWidget->setWindowTitle(QCoreApplication::translate("InfoWidget", "Form", nullptr));
        label_delay->setText(QString());
        label_bn_t->setText(QCoreApplication::translate("InfoWidget", "Block Number:", nullptr));
        label_delay_t->setText(QCoreApplication::translate("InfoWidget", "Block ID&Delay:", nullptr));
        label_bn->setText(QString());
        pushButton->setText(QString());
        label_cid_t->setText(QCoreApplication::translate("InfoWidget", "Client ID:", nullptr));
        label_cid->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class InfoWidget: public Ui_InfoWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INFOWIDGET_H

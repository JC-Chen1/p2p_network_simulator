/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QFrame *frame;
    QPushButton *pushButton_start;
    QLabel *label;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1225, 764);
        MainWindow->setStyleSheet(QString::fromUtf8("QWidget\n"
"{\n"
"	background-color:transparent;\n"
"}\n"
"\n"
"QFrame\n"
"{\n"
"	background-color:white;\n"
"	border:none;\n"
"	border-radius:30px;\n"
"}\n"
""));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        frame = new QFrame(centralwidget);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(30, 0, 1091, 741));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton_start = new QPushButton(frame);
        pushButton_start->setObjectName("pushButton_start");
        pushButton_start->setGeometry(QRect(420, 450, 261, 101));
        pushButton_start->setStyleSheet(QString::fromUtf8("font: 28pt \"Poiret One\";\n"
"border-radius:15px;\n"
"background-color: rgb(71, 0, 213);\n"
"color:rgb(85, 255, 255)"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(360, 290, 381, 91));
        label->setStyleSheet(QString::fromUtf8("font: 26pt \"Poiret One\";"));
        label->setAlignment(Qt::AlignCenter);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 1225, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_start->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "P2P analog TV network", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

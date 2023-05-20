/********************************************************************************
** Form generated from reading UI file 'intro.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INTRO_H
#define UI_INTRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Intro
{
public:
    QFrame *frame;
    QPushButton *pushButton;
    QLabel *label;

    void setupUi(QWidget *Intro)
    {
        if (Intro->objectName().isEmpty())
            Intro->setObjectName("Intro");
        Intro->resize(657, 861);
        frame = new QFrame(Intro);
        frame->setObjectName("frame");
        frame->setGeometry(QRect(9, 19, 641, 861));
        frame->setStyleSheet(QString::fromUtf8("#frame{background-color: rgb(255, 255, 255);\n"
"	border-radius:25px;\n"
"	background-image: url(:/klee.jpg);\n"
"}\n"
"QLabel{\n"
"background-color: rgba(255, 255, 255,0.95);\n"
"font: 16pt \"Kozuka Mincho Pro R\";\n"
"border-radius:15px;\n"
"}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(570, 20, 41, 41));
        pushButton->setStyleSheet(QString::fromUtf8("background:transparent;\n"
"border-image: url(:/close.png);"));
        label = new QLabel(frame);
        label->setObjectName("label");
        label->setGeometry(QRect(180, 100, 331, 221));
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);

        retranslateUi(Intro);

        QMetaObject::connectSlotsByName(Intro);
    } // setupUi

    void retranslateUi(QWidget *Intro)
    {
        Intro->setWindowTitle(QCoreApplication::translate("Intro", "Form", nullptr));
        pushButton->setText(QString());
        label->setText(QCoreApplication::translate("Intro", "\n"
" \345\274\200\345\217\221\350\200\205\357\274\232\351\231\210\345\230\211\350\257\232\343\200\201\347\216\213\347\220\233\343\200\201\347\216\213\346\265\251\346\240\251\n"
" \350\203\214\346\231\257\345\233\276\347\211\207\346\235\245\346\272\220\357\274\232\n"
" \350\256\241\347\256\227\346\234\272\347\247\221\345\255\246\344\270\216\345\267\245\347\250\213\345\255\246\351\231\242\n"
" \350\256\241\347\247\2211\347\217\255 \345\275\255\344\274\237\347\220\252\347\232\204\346\234\200\347\210\261", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Intro: public Ui_Intro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INTRO_H

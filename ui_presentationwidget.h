/********************************************************************************
** Form generated from reading UI file 'presentationwidget.ui'
**
** Created by: Qt User Interface Compiler version 6.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PRESENTATIONWIDGET_H
#define UI_PRESENTATIONWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_presentationWidget
{
public:

    void setupUi(QWidget *presentationWidget)
    {
        if (presentationWidget->objectName().isEmpty())
            presentationWidget->setObjectName("presentationWidget");
        presentationWidget->resize(1200, 800);
        presentationWidget->setStyleSheet(QString::fromUtf8("QWidget{\n"
"	background-color: rgba(89, 89, 89,0.95)\n"
"}"));

        retranslateUi(presentationWidget);

        QMetaObject::connectSlotsByName(presentationWidget);
    } // setupUi

    void retranslateUi(QWidget *presentationWidget)
    {
        presentationWidget->setWindowTitle(QCoreApplication::translate("presentationWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class presentationWidget: public Ui_presentationWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PRESENTATIONWIDGET_H

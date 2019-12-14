/********************************************************************************
** Form generated from reading UI file 'mtoobox.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MTOOBOX_H
#define UI_MTOOBOX_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mtoobox
{
public:

    void setupUi(QWidget *Mtoobox)
    {
        if (Mtoobox->objectName().isEmpty())
            Mtoobox->setObjectName(QString::fromUtf8("Mtoobox"));
        Mtoobox->resize(400, 300);

        retranslateUi(Mtoobox);

        QMetaObject::connectSlotsByName(Mtoobox);
    } // setupUi

    void retranslateUi(QWidget *Mtoobox)
    {
        Mtoobox->setWindowTitle(QApplication::translate("Mtoobox", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Mtoobox: public Ui_Mtoobox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MTOOBOX_H

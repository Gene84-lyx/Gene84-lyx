/********************************************************************************
** Form generated from reading UI file 'mlabel.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MLABEL_H
#define UI_MLABEL_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mlabel
{
public:

    void setupUi(QWidget *Mlabel)
    {
        if (Mlabel->objectName().isEmpty())
            Mlabel->setObjectName(QString::fromUtf8("Mlabel"));
        Mlabel->resize(400, 300);

        retranslateUi(Mlabel);

        QMetaObject::connectSlotsByName(Mlabel);
    } // setupUi

    void retranslateUi(QWidget *Mlabel)
    {
        Mlabel->setWindowTitle(QApplication::translate("Mlabel", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Mlabel: public Ui_Mlabel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MLABEL_H

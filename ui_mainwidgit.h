/********************************************************************************
** Form generated from reading UI file 'mainwidgit.ui'
**
** Created by: Qt User Interface Compiler version 4.8.7
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWIDGIT_H
#define UI_MAINWIDGIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mainwidgit
{
public:

    void setupUi(QWidget *Mainwidgit)
    {
        if (Mainwidgit->objectName().isEmpty())
            Mainwidgit->setObjectName(QString::fromUtf8("Mainwidgit"));
        Mainwidgit->resize(400, 300);

        retranslateUi(Mainwidgit);

        QMetaObject::connectSlotsByName(Mainwidgit);
    } // setupUi

    void retranslateUi(QWidget *Mainwidgit)
    {
        Mainwidgit->setWindowTitle(QApplication::translate("Mainwidgit", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Mainwidgit: public Ui_Mainwidgit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWIDGIT_H

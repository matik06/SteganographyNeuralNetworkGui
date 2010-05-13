/********************************************************************************
** Form generated from reading ui file 'de.ui'
**
** Created: Thu May 13 12:09:24 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DE_H
#define UI_DE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_deClass
{
public:

    void setupUi(QDialog *deClass)
    {
        if (deClass->objectName().isEmpty())
            deClass->setObjectName(QString::fromUtf8("deClass"));
        deClass->resize(400, 300);

        retranslateUi(deClass);

        QMetaObject::connectSlotsByName(deClass);
    } // setupUi

    void retranslateUi(QDialog *deClass)
    {
        deClass->setWindowTitle(QApplication::translate("deClass", "de", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(deClass);
    } // retranslateUi

};

namespace Ui {
    class deClass: public Ui_deClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DE_H

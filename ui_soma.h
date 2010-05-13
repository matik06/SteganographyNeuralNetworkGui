/********************************************************************************
** Form generated from reading ui file 'soma.ui'
**
** Created: Thu May 13 12:09:24 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SOMA_H
#define UI_SOMA_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_SomaClass
{
public:

    void setupUi(QDialog *SomaClass)
    {
        if (SomaClass->objectName().isEmpty())
            SomaClass->setObjectName(QString::fromUtf8("SomaClass"));
        SomaClass->resize(400, 300);

        retranslateUi(SomaClass);

        QMetaObject::connectSlotsByName(SomaClass);
    } // setupUi

    void retranslateUi(QDialog *SomaClass)
    {
        SomaClass->setWindowTitle(QApplication::translate("SomaClass", "Soma", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SomaClass);
    } // retranslateUi

};

namespace Ui {
    class SomaClass: public Ui_SomaClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SOMA_H

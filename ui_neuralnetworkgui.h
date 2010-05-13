/********************************************************************************
** Form generated from reading ui file 'neuralnetworkgui.ui'
**
** Created: Thu May 13 12:09:24 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NEURALNETWORKGUI_H
#define UI_NEURALNETWORKGUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NeuralNetworkGuiClass
{
public:

    void setupUi(QWidget *NeuralNetworkGuiClass)
    {
        if (NeuralNetworkGuiClass->objectName().isEmpty())
            NeuralNetworkGuiClass->setObjectName(QString::fromUtf8("NeuralNetworkGuiClass"));
        NeuralNetworkGuiClass->resize(400, 300);

        retranslateUi(NeuralNetworkGuiClass);

        QMetaObject::connectSlotsByName(NeuralNetworkGuiClass);
    } // setupUi

    void retranslateUi(QWidget *NeuralNetworkGuiClass)
    {
        NeuralNetworkGuiClass->setWindowTitle(QApplication::translate("NeuralNetworkGuiClass", "NeuralNetworkGui", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(NeuralNetworkGuiClass);
    } // retranslateUi

};

namespace Ui {
    class NeuralNetworkGuiClass: public Ui_NeuralNetworkGuiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEURALNETWORKGUI_H

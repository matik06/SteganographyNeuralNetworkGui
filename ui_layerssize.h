/********************************************************************************
** Form generated from reading ui file 'layerssize.ui'
**
** Created: Thu May 13 12:09:24 2010
**      by: Qt User Interface Compiler version 4.5.2
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_LAYERSSIZE_H
#define UI_LAYERSSIZE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LayersSizeClass
{
public:

    void setupUi(QWidget *LayersSizeClass)
    {
        if (LayersSizeClass->objectName().isEmpty())
            LayersSizeClass->setObjectName(QString::fromUtf8("LayersSizeClass"));
        LayersSizeClass->resize(400, 300);

        retranslateUi(LayersSizeClass);

        QMetaObject::connectSlotsByName(LayersSizeClass);
    } // setupUi

    void retranslateUi(QWidget *LayersSizeClass)
    {
        LayersSizeClass->setWindowTitle(QApplication::translate("LayersSizeClass", "LayersSize", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LayersSizeClass);
    } // retranslateUi

};

namespace Ui {
    class LayersSizeClass: public Ui_LayersSizeClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LAYERSSIZE_H

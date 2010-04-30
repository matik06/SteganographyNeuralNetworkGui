/********************************************************************************
** Form generated from reading ui file 'networksettings.ui'
**
** Created: Wed Dec 9 02:15:07 2009
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_NETWORKSETTINGS_H
#define UI_NETWORKSETTINGS_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_NetworkSettingsClass
{
public:

    void setupUi(QWidget *NetworkSettingsClass)
    {
        if (NetworkSettingsClass->objectName().isEmpty())
            NetworkSettingsClass->setObjectName(QString::fromUtf8("NetworkSettingsClass"));
        NetworkSettingsClass->resize(400, 300);

        retranslateUi(NetworkSettingsClass);

        QMetaObject::connectSlotsByName(NetworkSettingsClass);
    } // setupUi

    void retranslateUi(QWidget *NetworkSettingsClass)
    {
        NetworkSettingsClass->setWindowTitle(QApplication::translate("NetworkSettingsClass", "NetworkSettings", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(NetworkSettingsClass);
    } // retranslateUi

};

namespace Ui {
    class NetworkSettingsClass: public Ui_NetworkSettingsClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NETWORKSETTINGS_H

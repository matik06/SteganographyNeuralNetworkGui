#ifndef NETWORKSETTINGS_H
#define NETWORKSETTINGS_H

class QGroupBox;
class QComboBox;
class QPushButton;
class QListWidget;
class QLabel;

#include <QtGui/QWidget>
#include <QDialog>
#include "ui_networksettings.h"
#include "layerssize.h"
#include "src/EnumTypes.h"
#include "soma.h"
#include "de.h"
#include <cstdio>


class NetworkSettings : public QDialog
{
    Q_OBJECT

public:
    NetworkSettings(QWidget *parent = 0);
    ~NetworkSettings();

public slots:
	//void showActivationFParam();
	void setLayersSize();
	void setNewLayersSize();
	void saveSettings();
	void learningAlgorithmSettings();

private:
    Ui::NetworkSettingsClass ui;

    QGroupBox * createLayersDetailsGroup();
    QGroupBox * createLearningAlgorithmDetailsGroup();

    void saveSettingsToSingleton();
    void updateDialog();

    //learning algorithm
    QComboBox * learningAlgorithmCombo;
    QComboBox * learningOType;
    Soma * somaDialog;
    DE * deDialog;
    QPushButton * learningAlrorithmButton;

    //layers
    QLineEdit * numberOfLayerLine;
    QPushButton * setLayerSizeButton;
    bool setLayersNumber;
    LayersSize * layersSize;
    QLineEdit * numberInputDataForNeuronLine;

    //save
    QPushButton * save;
};

#endif // NETWORKSETTINGS_H

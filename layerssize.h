#ifndef LAYERSSIZE_H
#define LAYERSSIZE_H

#include <QtGui/QWidget>
#include "ui_layerssize.h"
#include <QDialog>
#include "src/Singleton.h"
#include "src/EnumTypes.h"

class QLabel;
class QLineEdit;
class QPushButton;
class QComboBox;
class QVBoxLayout;
class QGroupBox;

class LayersSize : public QDialog
{
    Q_OBJECT

public:
    LayersSize(QWidget *parent = 0, int size = 3, int values[] = 0);
    ~LayersSize();

	void setDefaultValues();

public slots:

void showActivParameter();
void saveDetails();


private:

	int size;

	int * getLayersSize();
	void saveDataToSingleton();
	void readDataFromSingleton();


	QComboBox * getActivationCBox();
	QLineEdit * getLayerSizeLine();
	QLineEdit * getActivationParamLine();

	QString getLabelName(QString name, int n);

	QGroupBox * createLayerDetails(int n);
	QVBoxLayout * createMainLayout(int n);

	void initialization(int n);
	void reject();
	bool checkEmptyFields();


    QLabel ** layersLabel;
    QLineEdit ** layersEdit;

    QLabel ** activatiFunctionLabel;
    QComboBox ** activatiFunctionCheckBox;

    QLabel ** alfaLabel;
    QLineEdit ** alfaLine;

    QLabel ** betaLabel;
    QLineEdit ** betaLine;

    QPushButton * save;
};

#endif // LAYERSSIZE_H

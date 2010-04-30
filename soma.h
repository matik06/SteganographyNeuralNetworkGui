#ifndef SOMA_H
#define SOMA_H

class QLineEdit;
class QPushButton;
class QVBoxLayout;
class QCheckBox;

#include <QtGui/QDialog>
#include "Singleton.h"

class Soma : public QDialog
{
    Q_OBJECT

public:
    Soma(QWidget *parent = 0);
    ~Soma();

public slots:
    void accErrorAvaliable();
    void saveSettings();

private:

	QVBoxLayout * createSomaBoxLayout();
	bool validatingDialog();
	bool isEmpty(QLineEdit * lineEdit, QString name);
	bool checkPathLengthDiviteByPath();
	void saveDataToSingleton();
	void initialization();

	QLineEdit * popSizeLine;
	QLineEdit * stepLine;
	QLineEdit * pathLenghtLine;
	QLineEdit * PRTLine;
	QCheckBox * accErrorCheckBox;
	QLineEdit * accErrorLine;
	QLineEdit * migrationsLine;


	QPushButton * saveButton;
};

#endif // SOMA_H

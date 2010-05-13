#ifndef DE_H
#define DE_H

#include <QtGui/QDialog>
#include "src/Singleton.h"

class QPushButton;
class QLineEdit;
class QVBoxLayout;
class QString;

class DE : public QDialog
{
    Q_OBJECT

public:
    DE(QWidget *parent = 0);
    ~DE();

public slots:

	void saveSettings();

private:

	QVBoxLayout * createDEBoxLayout();
	bool validatingDialog();
	bool isEmpty(QLineEdit * lineEdit, QString name);
	void saveDataToSingleton();
	void initialization();

    QLineEdit * popSizeLine;
    QLineEdit * iterationsLine;
    QLineEdit * crossoverLine;
    QLineEdit * mutationConstantLine;

    QPushButton * saveButton;

};

#endif // DE_H

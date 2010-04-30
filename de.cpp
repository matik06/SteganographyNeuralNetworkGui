#include "de.h"
#include <QtGui>

DE::DE(QWidget *parent)
    : QDialog(parent)
{

	QVBoxLayout * mainLayout = createDEBoxLayout();
	initialization();

	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

	setLayout(mainLayout);
	setWindowTitle(tr("DE Settings"));

}

DE::~DE()
{
	delete popSizeLine;
	delete iterationsLine;
	delete crossoverLine;
	delete mutationConstantLine;
}

QVBoxLayout * DE::createDEBoxLayout()
{
	QVBoxLayout * vBox = new QVBoxLayout();

	QRegExp rePopSize("[1-9]{1}[0-9]{0,3}");
	QRegExpValidator * validator1to9999 = new QRegExpValidator(rePopSize, 0);
	QRegExp re1to0("[0-1]{1}[.]{1}[0-9]{1,2}");
	QRegExpValidator * validator1to0 = new QRegExpValidator( re1to0, 0);

	QLabel * popSizeLabel = new QLabel(tr("Population size"));
	popSizeLine = new QLineEdit();
	popSizeLine->setValidator(validator1to9999);

	QLabel * iterationsLabel = new QLabel(tr("Number of iterations"));
	iterationsLine = new QLineEdit();
	iterationsLine->setValidator(validator1to9999);

	QLabel * crossoverLabel = new QLabel(tr("Crossover"));
	crossoverLine = new QLineEdit();
	crossoverLine->setValidator(validator1to0);

	QLabel * mutationConstantLabel = new QLabel(tr("Mutation Constant"));
	mutationConstantLine = new QLineEdit();
	mutationConstantLine->setValidator(validator1to0);

	saveButton = new QPushButton(tr("&Save DE Settings"));

	vBox->addWidget(popSizeLabel);
	vBox->addWidget(popSizeLine);
	vBox->addWidget(iterationsLabel);
	vBox->addWidget(iterationsLine);
	vBox->addWidget(crossoverLabel);
	vBox->addWidget(crossoverLine);
	vBox->addWidget(mutationConstantLabel);
	vBox->addWidget(mutationConstantLine);
	vBox->addWidget(saveButton);

	vBox->stretch(1);
	return vBox;
}

void DE::initialization()
{
	QString tmp;

	popSizeLine->setText( tmp.setNum(dataSettings().popSizeDE) );
	iterationsLine->setText(tmp.setNum(dataSettings().iterations));
	crossoverLine->setText(tmp.setNum(dataSettings().crossover));
	mutationConstantLine->setText(tmp.setNum(dataSettings().mutationConstant));
}

bool DE::isEmpty(QLineEdit * lineEdit, QString name)
{
	if( lineEdit->text().isEmpty() )
	{
		QMessageBox::information(this, tr("Missing data"),
						 tr("Sorry, \"%1\" number can't be empty.").arg(name));
		return true;
	}
	else
		return false;
}

bool DE::validatingDialog()
{
	bool empty[4];

	empty[0] = isEmpty(popSizeLine, tr("Population Size"));
	empty[1] = isEmpty(iterationsLine, tr("Iterations number"));
	empty[2] = isEmpty(crossoverLine, tr("Crossover"));
	empty[3] = isEmpty(mutationConstantLine, tr("Mutation Constant"));

	for(int i = 0; i < 4; i++)
	{
		if( empty[i] == true )
		{
			return false;
		}
	}

	return true;
}

void DE::saveDataToSingleton()
{
	dataSettings().popSizeDE = popSizeLine->text().toInt();
	dataSettings().iterations = iterationsLine->text().toInt();
	dataSettings().crossover = crossoverLine->text().toDouble();
	dataSettings().mutationConstant = mutationConstantLine->text().toDouble();
}

void DE::saveSettings()
{
	if(validatingDialog())
	{
		saveDataToSingleton();
		accept();
	}
}

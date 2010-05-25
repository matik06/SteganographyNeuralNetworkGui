#include "soma.h"
#include <QtGui>

Soma::Soma(QWidget *parent)
    : QDialog(parent)
{
	setModal(true);

	QVBoxLayout * mainLayout = createSomaBoxLayout();
	initialization();

	connect(accErrorCheckBox, SIGNAL(stateChanged(int)), this, SLOT(accErrorAvaliable()));
	connect(saveButton, SIGNAL(clicked()), this, SLOT(saveSettings()));

	setLayout(mainLayout);
	setWindowTitle(tr("SOMA Settings"));
}

Soma::~Soma()
{
	delete popSizeLine;
	delete stepLine;
	delete pathLenghtLine;
	delete PRTLine;
	delete accErrorLine;
	delete migrationsLine;

	delete saveButton;
}

QVBoxLayout * Soma::createSomaBoxLayout()
{
	QVBoxLayout * vBox = new QVBoxLayout();

	QRegExp rePopSize("[1-9]{1}[0-9]{0,3}");
	QRegExpValidator * validator1to9999 = new QRegExpValidator(rePopSize, 0);
	QRegExp reStep("[0-9]{1,3}[.]{0,1}[0-9]{1,3}");
	QRegExpValidator * validatorStepPath = new QRegExpValidator(reStep, 0);
	QRegExp rePRT("[0-1]{1}[.]{1}[0-9]{1,2}");
	QRegExpValidator * validatorPRT = new QRegExpValidator( rePRT, 0);
	QRegExp reAccError("[0-9]{1,4}[.]{0,1}[0-9]{1,5}");
	QRegExpValidator * validatorAccError = new QRegExpValidator( reAccError, 0);

	QLabel * popSizeLabel = new QLabel(tr("Population size"));
	popSizeLine = new QLineEdit();
	popSizeLine->setValidator(validator1to9999);

	QLabel * stepLabel = new QLabel(tr("Step"));
	stepLine = new QLineEdit();
	stepLine->setValidator(validatorStepPath);

	QLabel * pathLenghtLabel = new QLabel(tr("Path length"));
	pathLenghtLine = new QLineEdit();
	pathLenghtLine->setValidator( validatorStepPath );

	QLabel * PRTLabel = new QLabel(tr("PRT"));
	PRTLine = new QLineEdit();
	PRTLine->setValidator( validatorPRT );

	accErrorCheckBox = new QCheckBox(tr("Accuracy Error"));
	accErrorLine = new QLineEdit();
	accErrorLine->setValidator( validatorAccError );
	accErrorLine->setEnabled(false);

	accErrorLine->setVisible(false);
	accErrorCheckBox->setVisible(false);

	QLabel * MigrationsLabel = new QLabel(tr("Migrations"));
	migrationsLine = new QLineEdit();
	migrationsLine->setValidator( validator1to9999 );

	saveButton = new QPushButton(tr("&Save SOMA settings"));

	vBox->addWidget(MigrationsLabel);
	vBox->addWidget(migrationsLine);
	vBox->addWidget(popSizeLabel);
	vBox->addWidget(popSizeLine);
	vBox->addWidget(stepLabel);
	vBox->addWidget(stepLine);
	vBox->addWidget(pathLenghtLabel);
	vBox->addWidget(pathLenghtLine);
	vBox->addWidget(PRTLabel);
	vBox->addWidget(PRTLine);
	vBox->addWidget(accErrorCheckBox);
	vBox->addWidget(accErrorLine);
	vBox->addWidget(saveButton);

	vBox->stretch(1);
	return vBox;
}

void Soma::accErrorAvaliable()
{
	if(accErrorCheckBox->checkState() == Qt::Checked)
	{
		this->accErrorLine->setEnabled(true);
			accErrorLine->clear();
	}
	else if(accErrorCheckBox->checkState() == Qt::Unchecked)
	{
		this->accErrorLine->setEnabled(false);
		this->accErrorLine->setText(tr("-1"));
	}
}

bool Soma::isEmpty(QLineEdit * lineEdit, QString name)
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

bool Soma::checkPathLengthDiviteByPath()
{
	double pathLength = pathLenghtLine->text().toDouble();
	double step = stepLine->text().toDouble();

	if( (pathLength / step) < 1 )
	{
		QMessageBox::information(this, tr("Incorrect data"),
				                 tr("Path Length / step have to be higher then 1"));
		return false;
	}
	else
		return true;
}

bool Soma::validatingDialog()
{
	bool empty[6];

	empty[0] = isEmpty(migrationsLine, tr("Migrations"));
	empty[1] = isEmpty(popSizeLine, tr("Population"));
	empty[2] = isEmpty(stepLine, tr("Step"));
	empty[3] = isEmpty(pathLenghtLine, tr("Path Length"));
	empty[4] = isEmpty(PRTLine, tr("PRT"));


	if( accErrorCheckBox->checkState() == Qt::Checked )
	{
		empty[5] = isEmpty(accErrorLine, tr("Accuracy Error"));
	}
	else
		empty[5] = false;

	bool anyEmpty = false;
	for(int i = 0; i < 6; i++)
	{
		if(empty[i] == true)
		{
			anyEmpty = true;
			break;
		}
	}

	if(anyEmpty)
		return false;
	else
	{
		if (checkPathLengthDiviteByPath())
			return true;
		else
			return false;
	}
}

void Soma::saveDataToSingleton()
{
	dataSettings().migrations = migrationsLine->text().toInt();
	dataSettings().popSizeSoma = popSizeLine->text().toInt();

	dataSettings().step = stepLine->text().toDouble();
	dataSettings().pathLength = pathLenghtLine->text().toDouble();
	dataSettings().PRT = PRTLine->text().toDouble();

	if( accErrorCheckBox->checkState() == Qt::Checked )
		dataSettings().accError = accErrorLine->text().toDouble();
	else
		dataSettings().accError = -1;
}

void Soma::saveSettings()
{
	if( validatingDialog() )
	{
		saveDataToSingleton();
		accept();
	}
}

void Soma::initialization()
{
	QString tmp;

	migrationsLine->setText( tmp.setNum(dataSettings().migrations) );
	popSizeLine->setText( tmp.setNum(dataSettings().popSizeSoma) );
	stepLine->setText( tmp.setNum(dataSettings().step) );
	pathLenghtLine->setText( tmp.setNum(dataSettings().pathLength) );
	PRTLine->setText( tmp.setNum(dataSettings().PRT) );


	if( dataSettings().accError == -1 )
	{
		accErrorCheckBox->setCheckState(Qt::Unchecked);
		accErrorLine->setEnabled(false);
		accErrorLine->setText(tr("-1"));
	}
	else
	{
		accErrorCheckBox->setCheckState(Qt::Checked);
		accErrorLine->setEnabled(true);
		accErrorLine->setText(tmp.setNum(dataSettings().accError));
	}
}

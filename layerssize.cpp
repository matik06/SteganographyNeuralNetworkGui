#include "layerssize.h"
#include <QtGui>

LayersSize::LayersSize(QWidget *parent, int size, int values[])
    : QDialog(parent), size(size)
{
	setModal(true);

	dataSettings().weightsNumber;

	initialization(size);
	QVBoxLayout * mainLayout = createMainLayout(size);
	readDataFromSingleton();
	mainLayout->addWidget(save);

	for(int i = 0; i < size; i++)
	{
		connect( activatiFunctionCheckBox[i], SIGNAL(currentIndexChanged(int)), this,
				SLOT( showActivParameter()) );
	}
	connect(save, SIGNAL(clicked()), this, SLOT(saveDetails()));
	connect(this, SIGNAL(rejected()), this, SLOT(saveDetails()));


	setLayout( mainLayout );
	setWindowTitle(tr("Layers size"));

}



LayersSize::~LayersSize()
{
	for(int i = 0; i < size; i++)
	{
		delete layersLabel[i];
		delete layersEdit[i];

		delete activatiFunctionLabel[i];
		delete activatiFunctionCheckBox[i];

		delete alfaLabel[i];
		delete alfaLine[i];

		delete betaLabel[i];
		delete betaLine[i];
	}

	delete [] layersEdit;
	delete [] layersLabel;
	delete [] activatiFunctionLabel;
	delete [] activatiFunctionCheckBox;
	delete [] alfaLabel;
	delete [] alfaLine;
	delete [] betaLabel;
	delete [] betaLine;

	delete save;
}

void LayersSize::initialization(int n)
{
	layersLabel = new QLabel*[n];
	layersEdit = new QLineEdit*[n];
	activatiFunctionLabel = new QLabel*[n];
	activatiFunctionCheckBox = new QComboBox*[n];
	alfaLabel = new QLabel*[n];
	alfaLine = new QLineEdit*[n];
	betaLabel = new QLabel*[n];
	betaLine = new QLineEdit*[n];
	save = new QPushButton(tr("&Save"));
}

void LayersSize::saveDetails()
{
	if(!checkEmptyFields())
	{
		saveDataToSingleton();
		accept();
	}
}


void LayersSize::reject()
{
	saveDetails();
}

int * LayersSize::getLayersSize()
{
	int * result = new int[size];

	for(int i = 0; i < size; i++)
	{
		result[i] = layersEdit[i]->text().toInt();
	}

	return result;
}

QLineEdit * LayersSize::getLayerSizeLine()
{
	QLineEdit * layerSizeLine = new QLineEdit();

	QRegExp re("[1-9]{1}[0-9]{2}");
	QRegExpValidator * validator = new QRegExpValidator(re, 0);

	layerSizeLine->setValidator(validator);

	return layerSizeLine;
}

QComboBox * LayersSize::getActivationCBox()
{
	QComboBox * activationCB = new QComboBox();

	activationCB->insertItem(0, tr("Sigmoidal UP"));
	activationCB->insertItem(1, tr("Sigmoidal BP"));
	activationCB->insertItem(2, tr("Tanh"));
	activationCB->insertItem(3, tr("Linear"));


	return activationCB;
}

QLineEdit * LayersSize::getActivationParamLine()
{
	QLineEdit * paramLine = new QLineEdit();

	QRegExp re("[0]{1}[.]{1}[0-9]{2}");
	QRegExpValidator * validator = new QRegExpValidator(re, 0);

	paramLine->setValidator(validator);

	return paramLine;
}

QString LayersSize::getLabelName( QString name, int n )
{
	QString tmp;
	QString result = name;

	result += ": ";
	result += tmp.setNum(n);

	return result;
}


QGroupBox * LayersSize::createLayerDetails( int i )
{
	QGridLayout * gridLayout = new QGridLayout();
	QString title;

	title = getLabelName(tr("Number of Neurons in Layer"), i);
	layersLabel[i] = new QLabel( title );
	layersEdit[i] = getLayerSizeLine();
	title = getLabelName(tr("Select Activation Function in Layer"), i);
	activatiFunctionLabel[i] = new QLabel( title );
	activatiFunctionCheckBox[i] = getActivationCBox();

	QVBoxLayout * left = new QVBoxLayout();
	left->addWidget(layersLabel[i]);
	left->addWidget(layersEdit[i]);
	left->addWidget(activatiFunctionLabel[i]);
	left->addWidget(activatiFunctionCheckBox[i]);
	left->stretch(1);

	title = getLabelName(tr("Alfa Parameter for Neurons in Layer"), i);
	alfaLabel[i] = new QLabel( title );
	alfaLine[i] = getActivationParamLine();
	title = getLabelName(tr("Beta Parameter for Neurons in Layer"), i);
	betaLabel[i] = new QLabel( title );
	betaLine[i] = getActivationParamLine();

	QVBoxLayout * right = new QVBoxLayout();
	right->addWidget(alfaLabel[i]);
	right->addWidget(alfaLine[i]);
	right->addWidget(betaLabel[i]);
	right->addWidget(betaLine[i]);
	right->stretch(1);

	gridLayout->addLayout(left, 0, 0);
	gridLayout->addLayout(right, 0, 1);

	title = getLabelName(tr("Layer nr"), i);
	QGroupBox * groupBox = new QGroupBox(title);
	groupBox->setLayout(gridLayout);

	return groupBox;
}

QVBoxLayout * LayersSize::createMainLayout(int n)
{
	QVBoxLayout * vBox = new QVBoxLayout();

	for(int i = 0; i < n; i++)
	{
		vBox->addWidget( createLayerDetails(i) );
	}

	return vBox;
}

void LayersSize::showActivParameter()
{
	for(int i = 0; i < size; i++)
	{
		int index = activatiFunctionCheckBox[i]->currentIndex();

		if(index == 0 || index == 1)
		{
			betaLine[i]->setEnabled(true);
			alfaLine[i]->setEnabled(false);
		}
		else if(index == 2)
		{
			alfaLine[i]->setEnabled(true);
			betaLine[i]->setEnabled(false);
		}
		else if(index == 3)
		{
			alfaLine[i]->setEnabled(false);
			betaLine[i]->setEnabled(false);
		}
	}

}

bool LayersSize::checkEmptyFields()
{
	bool result = false;
	int index;

	for(int i = 0; i < size; i++)
	{
		if(this->layersEdit[i]->text().isEmpty())
		{
			result = true;
			QMessageBox::warning(this, tr("Missing data"),
							tr("One or more field with neuron numbers is empty!"));
			break;
		}
	}

	for(int i = 0; i < size; i++)
		{
			index = activatiFunctionCheckBox[i]->currentIndex();
			if(index == 0 ||  index == 1)
			{
				if(betaLine[i]->text().isEmpty())
				{
					result = true;
					QMessageBox::warning(this, tr("Missing data"),
							tr("One or more Beta number is empty!"));
					break;
				}
			}
			else if(index == 2)
			{
				if(alfaLine[i]->text().isEmpty())
				{
					result = true;
					QMessageBox::warning(this, tr("Missing data"),
							tr("One or more Alfa number is empty!"));
					break;
				}
			}
		}

	return result;
}

void LayersSize::saveDataToSingleton()
{
	double * alfaParameters = new double[size];
	double * betaParameters = new double[size];
	int index;
	KindOfNeuron::Enum * neuronsType = new KindOfNeuron::Enum[size];

	for(int i = 0; i < size; i++)
	{
		index = activatiFunctionCheckBox[i]->currentIndex();
		if(index == 0 )
		{
			neuronsType[i] = KindOfNeuron::SIGMOIDAL_UP_NEURON;
			betaParameters[i] = betaLine[i]->text().toDouble();
			alfaParameters[i] = 0.5;
		}
		else if(index == 1)
		{
			neuronsType[i] = KindOfNeuron::SIGMOIDAL_BP_NEURON;
			betaParameters[i] = betaLine[i]->text().toDouble();
			alfaParameters[i] = 0.5;
		}
		else if(index == 2)
		{
			neuronsType[i] = KindOfNeuron::TANH_NEURON;
			alfaParameters[i] = alfaLine[i]->text().toDouble();
			betaParameters[i] = 0.5;
		}
		else if(index == 3)
		{
			neuronsType[i] = KindOfNeuron::LINEAR;
			alfaParameters[i] = 0.5;
			betaParameters[i] = 0.5;
		}
	}

	dataSettings().layersSize = getLayersSize();
	dataSettings().neuronType = neuronsType;
	dataSettings().alfa = alfaParameters;
	dataSettings().beta = betaParameters;
}

void LayersSize::setDefaultValues()
{
	for(int i = 0; i < size; i++)
		{
			layersEdit[i]->setText( tr("10") );

			activatiFunctionCheckBox[i]->setCurrentIndex(0);
			betaLine[i]->setText( tr("0.5") );
			betaLine[i]->setEnabled(true);
			alfaLine[i]->setText( tr("0.5") );
			alfaLine[i]->setEnabled(false);
		}
}

void LayersSize::readDataFromSingleton()
{
	QString tmp;

		for(int i = 0; i < size; i++)
		{
			layersEdit[i]->setText( tmp.setNum(dataSettings().layersSize[i]) );

			if( dataSettings().neuronType[i] == KindOfNeuron::SIGMOIDAL_UP_NEURON)
			{
				activatiFunctionCheckBox[i]->setCurrentIndex(0);
				betaLine[i]->setText( tmp.setNum(dataSettings().beta[i]) );
				betaLine[i]->setEnabled(true);
				alfaLine[i]->setText( tr("0.5") );
				alfaLine[i]->setEnabled(false);
			}
			else if(dataSettings().neuronType[i] == KindOfNeuron::SIGMOIDAL_BP_NEURON)
			{
				activatiFunctionCheckBox[i]->setCurrentIndex(1);
				betaLine[i]->setText( tmp.setNum(dataSettings().beta[i]) );
				betaLine[i]->setEnabled(true);
				alfaLine[i]->setText( tr("0.5") );
				alfaLine[i]->setEnabled(false);
			}
			else if( dataSettings().neuronType[i] == KindOfNeuron::TANH_NEURON)
			{
				activatiFunctionCheckBox[i]->setCurrentIndex(2);
				betaLine[i]->setText( tr("0.5") );
				betaLine[i]->setEnabled(false);
				alfaLine[i]->setText( tmp.setNum(dataSettings().alfa[i]) );
				alfaLine[i]->setEnabled(true);
			}
			else if (dataSettings().neuronType[i] == KindOfNeuron::LINEAR)
			{
				activatiFunctionCheckBox[i]->setCurrentIndex(3);
				betaLine[i]->setText( tr("0.5") );
				betaLine[i]->setEnabled( false );
				alfaLine[i]->setText( tr("0.5") );
				alfaLine[i]->setEnabled( false );
			}
		}
}



#include "networksettings.h"
#include <QtGui>

NetworkSettings::NetworkSettings(QWidget *parent)
    : QDialog(parent)
{
	setModal(true);
	ui.setupUi(this);

	layersSize = 0;
	setLayersNumber = true;
	somaDialog = new Soma();
	deDialog = new DE();

	save = new QPushButton(tr("&Save Settings"));

	QGridLayout * mainLayout = new QGridLayout();
	mainLayout->addWidget(createLayersDetailsGroup(), 0, 0);
	mainLayout->addWidget(createLearningAlgorithmDetailsGroup(), 2, 0);
	mainLayout->addWidget(createOtherDetailsGroup(), 3, 0);
	mainLayout->addWidget(save, 4, 0);

	updateDialog();

	connect(setLayerSizeButton, SIGNAL(clicked()), this, SLOT(setLayersSize()));
	connect(numberOfLayerLine, SIGNAL(textChanged(QString)), this, SLOT(setNewLayersSize()));
	connect(save, SIGNAL(clicked()), this, SLOT(saveSettings()));
	connect(learningAlrorithmButton, SIGNAL(clicked()), this, SLOT(learningAlgorithmSettings()));
	connect(biasCheckBox, SIGNAL(stateChanged(int)), this, SLOT(bias()));

    setLayout(mainLayout);
    setWindowTitle(tr("Neural Network Settings"));
}

NetworkSettings::~NetworkSettings()
{
	delete learningAlgorithmCombo;
	delete learningOType;
	delete learningAlrorithmButton;

	delete numberOfLayerLine;
	delete setLayerSizeButton;
	delete layersSize;

	delete minRangeLine;
	delete maxRangeLine;

	delete biasCheckBox;
	delete biasLine;

	delete save;
}

QGroupBox * NetworkSettings::createOtherDetailsGroup()
{
	QGroupBox * groupBox = new QGroupBox( tr("Other Details:") );

	QLabel * weightsRangeLabel =  new QLabel("Weights range (min, max):");
	QLabel * biasLabel = new QLabel("Bias (for neurons in first layer)");

	biasCheckBox = new QCheckBox();
	biasLine = new QLineEdit();
	QHBoxLayout * hBox0 = new QHBoxLayout();
	hBox0->addWidget( biasCheckBox );
	hBox0->addWidget( biasLine );

	minRangeLine = new QLineEdit();
	maxRangeLine = new QLineEdit();

	QHBoxLayout * hBox = new QHBoxLayout();
	hBox->addWidget(minRangeLine);
	hBox->addWidget(maxRangeLine);

	QVBoxLayout * vBox = new QVBoxLayout();
	vBox->addWidget(weightsRangeLabel);
	vBox->addLayout( hBox );
	vBox->addWidget( biasLabel );
	vBox->addLayout( hBox0 );

	groupBox->setLayout( vBox );

	return groupBox;
}

QGroupBox *NetworkSettings::createLayersDetailsGroup()
{
	 QGroupBox *groupBox = new QGroupBox(tr("Layers Details:"));

	 QLabel * layerNumberLabel = new QLabel(tr("Number of layers:"));
	 numberOfLayerLine = new QLineEdit();
	 numberOfLayerLine->setMaxLength(1);
	 setLayerSizeButton = new QPushButton(tr("Change Layers size"));

	 QLabel * numberInputDataForNeuronLabel = new QLabel(tr("Number of Input Data for Single Neuron"));
	 numberInputDataForNeuronLine = new QLineEdit();

	 QRegExp re("[1-4]{1}");
	 QRegExpValidator * validator = new QRegExpValidator(re, 0);
	 QRegExp reInputs("[1-9]{1}[0-9]{0,3}");
	 QRegExpValidator * validatorInputs = new QRegExpValidator(reInputs, 0);

	 numberOfLayerLine->setValidator(validator);
	 numberInputDataForNeuronLine->setValidator(validatorInputs);

	 QVBoxLayout * vBox = new QVBoxLayout;
	 vBox->addWidget(layerNumberLabel);
	 vBox->addWidget(numberOfLayerLine);
	 vBox->addWidget(setLayerSizeButton);
	 vBox->addWidget(numberInputDataForNeuronLabel);
	 vBox->addWidget(numberInputDataForNeuronLine);

	 groupBox->setLayout(vBox);

	 return groupBox;
}

QGroupBox * NetworkSettings::createLearningAlgorithmDetailsGroup()
{
	 QGroupBox *groupBox = new QGroupBox(tr("Learning Algorithm Details:"));

	 QLabel * learningAlgorithmLabel = new QLabel(tr("Learning Algorithm:"));
	 learningAlgorithmCombo = new QComboBox();
	 learningAlgorithmCombo->insertItem(0, tr("SOMA"));
	 learningAlgorithmCombo->insertItem(1, tr("Differential Evolution"));

	 QLabel * learningOTypeLabel = new QLabel(tr("Optimization Type:"));
	 learningOType = new QComboBox();
	 learningOType->insertItem(0, tr("MIN"));
	 learningOType->insertItem(1, tr("MAX"));

	 learningAlrorithmButton = new QPushButton( tr("Learning Algorithm Settings") );

	 QVBoxLayout * vBox = new QVBoxLayout();
	 vBox->addWidget(learningAlgorithmLabel);
	 vBox->addWidget(learningAlgorithmCombo);
	 vBox->addWidget(learningOTypeLabel);
	 vBox->addWidget(learningOType);
	 vBox->addWidget(learningAlrorithmButton);
	 vBox->addStretch(1);

	 groupBox->setLayout(vBox);

	 return groupBox;
}

void NetworkSettings::setLayersSize()
{
	if(layersSize == 0)
	{
		layersSize = new LayersSize(this, dataSettings().nrOfLayers);
		layersSize->show();
	}
	else
	layersSize->show();
}

void NetworkSettings::setNewLayersSize()
{
	if(!numberOfLayerLine->text().isEmpty())
	{
		if(layersSize == 0)
		{
			layersSize = new LayersSize(this, numberOfLayerLine->text().toInt());
			layersSize->setDefaultValues();
			layersSize->show();
		}
		else
		{
			//deleting old form
			delete layersSize;
			layersSize = 0;

			//creating new form
			layersSize = new LayersSize(this, numberOfLayerLine->text().toInt());
			layersSize->setDefaultValues();
			layersSize->show();
		}
	}
}

void NetworkSettings::learningAlgorithmSettings()
{
	if( learningAlgorithmCombo->currentIndex() == 0 )
	{
		somaDialog->exec();
	}
	else if( learningAlgorithmCombo->currentIndex() == 1 )
	{
		deDialog->exec();
	}
}

void NetworkSettings::saveSettings()
{
	bool layers = numberOfLayerLine->text().isEmpty();

	if(layers)
	{
		QMessageBox::warning(this, tr("Missing data"),
					                tr("Numbers of layers data is empty!"));
	}

	else if( numberInputDataForNeuronLine->text().isEmpty() )
	{
		QMessageBox::warning(this, tr("Missing data"),
										                tr("Number of inputs in neurons is empty!"));
	}
	else if ( minRangeLine->text().isEmpty() || maxRangeLine->text().isEmpty() )
	{
		QMessageBox::warning(this, tr("Missing data"),
				tr("One of weights range number is empty!"));
	}
	else if ( biasCheckBox->isChecked() && biasLine->text().isEmpty() )
	{
			QMessageBox::warning(this, tr("Missing data"),
							tr("Bias Value is empty"));
	}
	else
	{
		saveSettingsToSingleton();
		accept();
	}

}

void NetworkSettings::saveSettingsToSingleton()
{
	int indexOptymalizationType = learningOType->currentIndex();
	if(indexOptymalizationType == 0)
	{
		dataSettings().oType = OptymalizationType::MINIMIM;
	}
	else if(indexOptymalizationType == 1)
	{
		dataSettings().oType = OptymalizationType::MAXIMUM;
	}

	int indexEvolType = learningAlgorithmCombo->currentIndex();
	if(indexEvolType == 0)
	{
		dataSettings().EvolAlgorithm = EvolAlgorithm::SOMA;
	}
	else if(indexEvolType == 1)
	{
		dataSettings().EvolAlgorithm = EvolAlgorithm::DE;
	}

	dataSettings().nrOfLayers = numberOfLayerLine->text().toInt();
	dataSettings().nrInputData = numberInputDataForNeuronLine->text().toInt();

	dataSettings().minWeightRange = minRangeLine->text().toDouble();
	dataSettings().maxWeightRange = maxRangeLine->text().toDouble();

	if ( biasCheckBox->isChecked() )
	{
		dataSettings().bias = biasLine->text().toDouble();
	}
	else
	{
		dataSettings().bias = 0;
	}
}

void NetworkSettings::updateDialog()
{
	QString tmp;

	numberOfLayerLine->setText( tmp.setNum(dataSettings().nrOfLayers) );

	if( dataSettings().oType == OptymalizationType::MINIMIM )
	{
		learningOType->setCurrentIndex(0);
	}
	else if( dataSettings().oType == OptymalizationType::MAXIMUM )
	{
		learningOType->setCurrentIndex(1);
	}


	if(dataSettings().EvolAlgorithm == EvolAlgorithm::SOMA)
	{
		learningAlgorithmCombo->setCurrentIndex(0);
	}
	else if(dataSettings().EvolAlgorithm == EvolAlgorithm::DE)
	{
		learningAlgorithmCombo->setCurrentIndex(1);
	}

	numberInputDataForNeuronLine->setText(tmp.setNum(dataSettings().nrInputData));
	minRangeLine->setText( tmp.setNum( dataSettings().minWeightRange ) );
	maxRangeLine->setText( tmp.setNum( dataSettings().maxWeightRange ) );

	if ( dataSettings().bias == 0)
	{
		biasCheckBox->setChecked(false);
		biasLine->setText(tmp.setNum(0.0));
		biasLine->setEnabled(false);
	}
	else
	{
		biasCheckBox->setChecked(true);
		biasLine->setText(tmp.setNum(dataSettings().bias));
		biasLine->setEnabled(true);
	}
}

void NetworkSettings::bias()
{
	bool biasSelect = biasCheckBox->isChecked();

	if ( biasSelect )
	{
		biasLine->setEnabled(true);
	}
	else
	{
		biasLine->setEnabled(false);
	}
}

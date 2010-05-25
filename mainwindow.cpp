#include "mainwindow.h"
#include <QtGui>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
	neuralNetwork = NULL;
	evolutionaryAlgorithm = NULL;

	ui.setupUi(this);
	srand((int)time(NULL));

	WriteDataFile::createMainFolder();
	readSettingsFromFile();
	initializeNeuralNetworkObjects();

	QVBoxLayout * vBox = createButtonsLayout();

	connect(settingsButton, SIGNAL(clicked()), this, SLOT(settings()));
	connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));
	connect(exitButton, SIGNAL(clicked()), this, SLOT(close()));
	connect(learnNetworkButton, SIGNAL(clicked()), this, SLOT(learning()));
	connect(recognizeButton, SIGNAL(clicked()), this, SLOT(recognize()));
	connect(saveToFileButton,SIGNAL(clicked()),this , SLOT(saveToFile()));
	connect(importSettingsFromFileButton,SIGNAL(clicked()),this, SLOT(importSettings()));
	connect(expotrSettingsToFileButton,SIGNAL(clicked()),this,SLOT(exportSettings()));


	setLayout(vBox);
	setWindowTitle(tr("Recognition Tool"));

	setMaximumSize(300, 180);
}

MainWindow::~MainWindow()
{
	delete learnNetworkButton;
	delete recognizeButton;
	delete settingsButton;
	delete aboutButton;
	delete saveToFileButton;
	delete importSettingsFromFileButton;
	delete [] _inputs;
	delete [] _outputs;
	for(int i =0; i<_numOfInputData;i++)
	{
		delete[] *_inputsDouble;
	}
	delete[] _inputsDouble;
	delete networkSettings;

	delete neuralNetwork;
	delete evolutionaryAlgorithm;
}

QVBoxLayout * MainWindow::createButtonsLayout()
{
	inputData = false;
	learned = false;

	learnNetworkButton = new QPushButton(tr("&Learn Network"));
	recognizeButton = new QPushButton(tr("Start &Recognition"));
	saveToFileButton = new QPushButton(tr("Export Settings To &Text File"));
	expotrSettingsToFileButton = new QPushButton(tr("&Export Settings To Binary File"));
	importSettingsFromFileButton = new QPushButton(tr("&Import Settings From Binary File"));
	settingsButton = new QPushButton(tr("&Settings"));
	aboutButton = new QPushButton(tr("&About"));
	exitButton = new QPushButton(tr("E&xit"));

	QVBoxLayout * vBox = new QVBoxLayout();
	vBox->addWidget(learnNetworkButton);
	vBox->addWidget(recognizeButton);
	vBox->addWidget(settingsButton);
	vBox->addWidget(saveToFileButton);
	vBox->addWidget(expotrSettingsToFileButton);
	vBox->addWidget(importSettingsFromFileButton);
	vBox->addWidget(aboutButton);
	vBox->addWidget(exitButton);

	vBox->addStretch(1);

	networkSettings = new NetworkSettings(this);
	networkSettings->hide();

	stat = new LearningStacistics();
	stat->hide();

	return vBox;
}

void MainWindow::settings()
{
	networkSettings->show();
	if(networkSettings->exec() == QDialog::Accepted)
	{
		//save settings to file
		saveSettingsToFile(tr("settings.ns"), false);
		//initializing neural network and evolutionary algorithm
		initializeNeuralNetworkObjects();
	}

}

void MainWindow::about()
{
	QMessageBox::information(this, tr("About Information"),
									tr("Authors: \nMateusz Lubanski \nPiotr Ploszaj")
								   );
}

void MainWindow::learning()
{
	QString fileName = QFileDialog::getOpenFileName(this,
			tr("Open File with Patterns"), "",
			tr("txt file (*.txt);;All Files (*)"));
	  if (fileName.isEmpty())
	  {
		  QMessageBox::warning(this,tr("Learning Failed"),tr("Please choose pattern file before learning!!!"));
		  return;
	  }
	  //tutaj powinno być sprawdzenie pliku (czy liczba danych zgadza się z ustawieniami sieci)
	  else
	  {
		  ReadDataFile rdf = ReadDataFile( fileName );
		  double ** aInputs = NULL;
		  double ** aOutputs = NULL;

		  //initializing arrays with data from file
		  int iNrDataSets = rdf.loadFileWithInputs( dataSettings().nrInputData,
				  dataSettings().getOutputLayerSize(), aInputs, aOutputs );

		  evolutionaryAlgorithm->resetPopulation();
		  Individual ind = evolutionaryAlgorithm->simulate( dataSettings().oType,
				  *neuralNetwork, aInputs, aOutputs, iNrDataSets);

		  neuralNetwork->setWeights( ind.getParam() );

		  int iNrWeights = dataSettings().getNrWeights();
		  dataSettings().setWeights( ind.getParam(), iNrWeights );

		  LearningStacistics *s = new LearningStacistics();
		  s->showRessults( evolutionaryAlgorithm->getCostValueHistory() );

		  learned = true;

		  //deleting arrays
			for(int i = 0; i < iNrDataSets; i++)
			{
				delete [] aInputs[i];
				delete [] aOutputs[i];
			}
			delete [] aInputs;
			delete [] aOutputs;
	  }
//		    int nrPatterns = _getNumberOfLines(fileName);
//			double **inputs = new double*[dataSettings().nrInputData];
//			double **patterns = new double*[dataSettings().layersSize[dataSettings().nrOfLayers] -1];
//
//			for(int i = 0 ; i < nrPatterns;i++)
//			{
//				inputs[i] = new double[dataSettings().nrInputData];
//				patterns[i] = new double[dataSettings().layersSize[dataSettings().nrOfLayers-1]];
//			}

//			if(_getPatternsFromFile(fileName,inputs,patterns))
//			{
//
//				 ReadDataFile rdf = ReadDataFile( fileName );
//						  double ** inputs = NULL;
//						  double ** patterns = NULL;
//
//						  //initializing arrays with data from file
//						  int nrPatterns = rdf.loadFileWithInputs( dataSettings().nrInputData,
//								  dataSettings().getOutputLayerSize(), inputs, patterns );
//
//				initializeNeuralNetworkObjects();
//				neuralNetwork->setPatterns(patterns, nrPatterns);
//
//				Individual ind ;
//				ind = evolutionaryAlgorithm->simulate(dataSettings().oType, *neuralNetwork, inputs);
//				neuralNetwork->setWeights(ind.getParam());

//				dataSettings().weightsNumber = _getWeightsNr();
//				dataSettings().weights = new double[dataSettings().weightsNumber];
//
//
//				for(int i=0;i<dataSettings().weightsNumber;i++)
//				{
//					dataSettings().weights[i] = ind.getParam()[i];
//				}

//				LearningStacistics *s = new LearningStacistics();
//				s->showRessults(evolutionaryAlgorithm->getCostValueHistory());
//				learned = true;
//			}

//			for(int i = 0; i < nrPatterns; i++)
//			{
//				delete [] inputs[i];
//				delete [] patterns[i];
//			}
//			delete [] inputs;
//			delete [] patterns;
//	  }

}

void MainWindow::recognize()
{
	if(learned)
	{
		QString fileName = QFileDialog::getOpenFileName(this,
	         tr("Open File with Input Data"), "",
	         tr("text file(*.txt);;All(*)"));
		if (fileName.isEmpty())
		{
			return;
		}
		else
		{
			_numOfInputData = _getNumberOfLines(fileName);
			_inputs = new QString[_numOfInputData];
			_inputsDouble = new double*[_numOfInputData];
			for(int i =0;i < _numOfInputData;i++)
			{
				_inputsDouble[i]= new double[dataSettings().nrInputData];
			}
			if(getInputsFromFile(fileName,_inputsDouble,_inputs))
			{

				_outputs = new double*[_numOfInputData];
				for(int i = 0; i < _numOfInputData; i++)
				{
					_outputs[i] = neuralNetwork->getNeuralNetworkOutput(_inputsDouble[i]);
				}
				QString OnlyName = fileName.mid(0,(fileName.length()-4));
				_saveResultsToFile(OnlyName);
				QMessageBox::information(this,tr("Recognition Complete"),tr("Recognition complete"));
			}
			else
			{

			}
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Warning"),
									tr("Please learn neural network before you start recognition!"));
	}
}

void MainWindow::exportSettings()
{
	 QString fileName = QFileDialog::getSaveFileName(this,
		         tr("Export Settings To File"), "",
		         tr("Weights (*.nnw)"));
		 if (fileName.isEmpty())
		 {
			 return;
		 }
		 else
		 {
			 QString weightsSettings = fileName;
			 weightsSettings += ".nnw";
			 saveSettingsToFile(weightsSettings, true);
		 }
}
void MainWindow::saveToFile()
{
	 QString fileName = QFileDialog::getSaveFileName(this,
	         tr("Save Details"), "",
	         tr("Text File(*.txt);;All Files (*)"));
	 if (fileName.isEmpty())
	 {
		 return;
	 }
	 else
	 {
		 _saveNeuralNetworkSettings(fileName);
		 QString qs = "created file : "+fileName+"_settings.txt \n ";
		 QMessageBox::information(this,tr("Saving complete"), qs);
	 }
}

void MainWindow::importSettings()
{
	  QString fileName = QFileDialog::getOpenFileName(this,
		         tr("Imports Settings From File"), "",
				 tr("Weights (*.nnw)"));
	  if (fileName.isEmpty())
	  {
		  return;
	  }
	  else
	  {
		  ReadDataFile rdf = ReadDataFile(fileName);
		  rdf.loadSettingsFromFile(dataSettings(), true);
		  learned = true;
	  }
}

bool MainWindow::_checkInputFile(QString firstLine)
{
	int count ;
	count = firstLine.count(tr(","));
	if(count+1 ==dataSettings().nrInputData)
	{
		return true;
	}
		return false;
}

bool MainWindow::_checkPatternsFile(QString firstLine)
{
	int countIn,countOut ;
	int index  = firstLine.indexOf('}');
	QString inpStr,outStr;
	inpStr = firstLine.mid(0,index);
	outStr = firstLine.mid(index);
	countIn = inpStr.count(tr(","));
	countOut= outStr.count(tr(","));
	int outputs = dataSettings().nrOfLayers-1;
	if((countIn+1 ==dataSettings().nrInputData)&&
	   (countOut+1 == dataSettings().layersSize[outputs]))
	{
		return true;
	}
		return false;
}

bool MainWindow::_getPatternsFromFile(QString fileName,double** inputs,double**outputs)
{
		  _patternFileName = fileName;
		  QFile file(fileName);
		  if (!file.open(QIODevice::ReadOnly))
		  {
				 QMessageBox::information(this, tr("Unable to open file"),
					 file.errorString());
				 return false;
		  }
		  QTextStream in(&file);

		  int nrLine =0,iterNr =0;
		  QString number;
		  bool correctFile;
		  while((!in.atEnd()))
		  {
			  QString qs = in.readLine();
			  if(iterNr == 0)
			  {
				   correctFile = _checkPatternsFile(qs);
				   iterNr++;
			  }
			  if(correctFile)
			  {
				  std::string s= qs.toStdString();
				  int kI =0,kO=0, i=0 ,znOut =0;;
				  while(i<qs.length() && (znOut<2))
				  {
					  if((s[i]=='{') || (s[i]==','))
					  {
						  ++i;
						  number ="";
						  while( (s[i] != ',' ) && (s[i] != '}') )
						  {
							QChar QchTmp(s[i]);
							if((QchTmp.isDigit()) || (s[i]=='.'))
							{
								number+=s[i];
								++i;
							}
							else
							{
								 QMessageBox::warning(this,tr("Learning Failed"), tr("Incorrect format of file"));
								 return false;
							}
						  }
						  if(znOut ==0)
						  {
							  inputs[nrLine][kI] = number.toDouble();
							  number="";
							  ++kI;
						  }
						  else
						  if(znOut==1)
						  {
							  outputs[nrLine][kO] = number.toDouble();
							  number="";
							  ++kO;
 						  }
					  }
					  else
					  if(s[i]=='}')
					  {
						  ++i;
						  ++znOut;
					  }
					  else
					  {
						  ++i;
					  }
				  }
				  ++nrLine;
			  }
			  else
			  {
				  QMessageBox::warning(this,tr("Learning Failed"),
						  tr("Incorrect format of file with patterns"));
								  return false;
			  }
		  }
		  return true;
}

bool MainWindow::getInputsFromFile(QString fileName,double** inputsDouble, QString *inputs)
{
	  QFile file(fileName);
		  if (!file.open(QIODevice::ReadOnly))
		  {
				 QMessageBox::information(this, tr("Unable to open file"),
					 file.errorString());
				 return false;
		  }
		  QTextStream in(&file);
		  int iterNr =0,nrLine=0;
		  QString number;

		  bool correctFile;
		  while((!in.atEnd()))
		  {
			  QString qs = in.readLine();

			  if(iterNr == 0)
			  {
				   correctFile = _checkInputFile(qs);
				   iterNr++;
			  }
			  if(correctFile)
			  {
				  std::string s= qs.toStdString();
				  int nrInLine =0;
				  inputs[nrLine]= qs;
				  int i=0;
				  while(i<qs.length())
				  {
					  if((s[i]=='{') || (s[i]==','))
					  {
						  ++i;
						  number ="";
						  while( (s[i] != ',' ) && (s[i] != '}') )
						  {
							QChar QchTmp(s[i]);
							if((QchTmp.isDigit()) || (s[i]=='.'))
							{
								number+=s[i];
								++i;
							}
							else
							{
								 QMessageBox::warning(this,tr("Learning Failed"), tr("Incorrect format of file"));
								 return false;
							}
						  }

							  inputsDouble[nrLine][nrInLine] = number.toDouble();
							  number="";
							  ++nrInLine;
					  }
					  else
					  if(s[i]=='}')
					  {
						  ++i;
					  }
					  else
					  {
						  ++i;
					  }
				  }
				  ++nrLine;
			  }
			  else
			  {
				  QMessageBox::warning(this,tr("Learning Failed"),
						  tr("Incorrect format of file with patterns"));
								  return false;
			  }

		  }
		  return true;
}

int MainWindow::_getNumberOfLines(QString& fileName)
{
	QFile file(fileName);
	QTextStream in(&file);
	int nr = 0;
	if (!file.open(QIODevice::ReadOnly))
		{
				QMessageBox::information(this, tr("Unable to open file"),
					file.errorString());
				return -1;
		}
	else
	{
		QString qs;
		while(!in.atEnd())
		{
		  qs = in.readLine();
		  if(qs.contains(tr("{")))
		  {
			  ++nr;
		  }
		}
		file.close();
	}
	_numOfInputData = nr;
	return nr;
}

void MainWindow::_saveResultsToFile(QString fileName)
{
	if(!fileName.contains("_results"))
		 {
			 fileName +="_results";
		 }
	 if(!fileName.contains(".txt"))
	 {
		 fileName +=".txt";
	 }

		 QFile file(fileName);
		 if (!file.open(QIODevice::WriteOnly))
		 {
			 QMessageBox::information(this, tr("Unable to open file"),
			 file.errorString());
			 return;
		 }
		QTextStream out(&file);

		for(int i = 0; i<_numOfInputData; i++)
		{
			QString outString= _inputs[i];
			QString tmp ="";
			QString results="{";
			int nrOutputData = dataSettings().layersSize[dataSettings().nrOfLayers-1];
			for(int k =0 ; k < nrOutputData-1 ;k++)
			{
				tmp.setNum(_outputs[i][k]);
				tmp += ",";
				results+=tmp;
			}
			tmp.setNum(_outputs[i][nrOutputData-1]);
			results+=tmp;
			results+="}";
			outString +=results;
			out<<outString<<endl;
		}
		file.close();

}

void MainWindow::_saveNeuralNetworkSettings(QString fileName)
{
	if(!fileName.contains("_settings"))
	 {
		 fileName +="_settings";
	 }
	 if(!fileName.contains(".txt"))
	 {
		 fileName +=".txt";
	 }
	 if (fileName.isEmpty())
	 {
		 return;
	 }
	 else
	 {
		 QFile file(fileName);
		 if (!file.open(QIODevice::WriteOnly))
		 {
			 QMessageBox::information(this, tr("Unable to open file"),
			 file.errorString());
			 return;
		 }
		 QTextStream out(&file);
		 out<<"Neural Network Settings :\n"
			<<"   Number of input data :"<<dataSettings().nrInputData<<"\n"
		    <<"   Number of layers : "<< dataSettings().nrOfLayers<<"\n";

		 for(int i=0; i< dataSettings().nrOfLayers; i++)
		 {
			 out<<"      Layer nr."<<i<<":\n"
				<<_getKindOfNeuron(i)<<endl;
		 }

		 out<<endl;
		 out<<_getWeights();
		 out<< "Additional information: \n"
			<< "   Name of file with patterns : "
			<<_patternFileName << "\n ";
		 switch(dataSettings().EvolAlgorithm)
		 {
			 case EvolAlgorithm::SOMA:
			 {
	    			out<<_getSOMADetails();
	    			break;
	   		 }
			 case EvolAlgorithm::DE:
			 {
				 out<<_getDEDetails();
				 break;
			 }
		 }
		 out<<_getOptimalizationType()<<"\n ";
	 }
}

QString MainWindow::_getKindOfNeuron(int index)
{
	switch(dataSettings().neuronType[index])
	{
		case KindOfNeuron::SIGMOIDAL_BP_NEURON:
			{
				std::stringstream tmpSS;
				tmpSS  << "        Number of neurons: "<<dataSettings().layersSize[index] <<"\n"
					   << "        Type of neurons : SIGMOIDAL BIPOLAR NEURON \n"
				       << "           Beta :" << dataSettings().beta[index]<<"\n   ";
				QString qs(tmpSS.str().c_str());
				return qs;
			}
		case KindOfNeuron::SIGMOIDAL_UP_NEURON:
			{
				std::stringstream tmpSS;
				tmpSS  << "        Number of neurons: "<<dataSettings().layersSize[index] <<"\n"
					   << "        Type of neurons : SIGMOIDAL UIPOLAR NEURON \n    "
					   << "           Beta :" << dataSettings().beta[index]<<"\n   ";
				QString qs(tmpSS.str().c_str());
				return qs;
			}
		case KindOfNeuron::TANH_NEURON:
			{
				std::stringstream tmpSS;
				tmpSS  << "        Number of neurons: "<<dataSettings().layersSize[index] <<"\n"
					   << "        Type of neurons : SIGMOIDAL BIPOLAR NEURON \n    "
					   << "           Alpha :" << dataSettings().alfa[index]<<"\n   ";
				QString qs(tmpSS.str().c_str());
				return qs;
			}
		default:
			{
				return tr("error");
			}
	}
}

QString MainWindow::_getSOMADetails()
{
	std::stringstream tmpSS;
    tmpSS << "   Learning algorithm Name: SOMA\n"
          << "\t Step: " << dataSettings().step << "\n"
		  << "\t PathLength: " << dataSettings().pathLength << "\n"
          << "\t PTR: " << dataSettings().PRT << "\n"
          << "\t AccError: " << dataSettings().accError << "\n"
          << "\t Migrations: " << dataSettings().migrations << "\n"
          << "\t Population Size: " << dataSettings().popSizeSoma << "\n";

	QString qs(tmpSS.str().c_str());
    return qs;
}

QString MainWindow::_getDEDetails()
{
    std::stringstream tmpSS;
    tmpSS << "   Learning algorithm Name: Differential Evolution\n"
          << "\t Mutation Constant: " << dataSettings().mutationConstant << " \n"
		  << "\t Crossover Probability: " << dataSettings().crossover << "\n"
          << "\t Population Size: " << dataSettings().popSizeDE << "\n"
          << "\t Number of iterations: " << dataSettings().iterations << "\n";

	QString qs(tmpSS.str().c_str());
    return qs;
};

QString MainWindow::_getOptimalizationType()
{
	switch(dataSettings().oType)
		{
			case OptymalizationType::MINIMIM:
				{
					std::stringstream tmpSS;
					QString qs = tr("   Kind of extremum: MIMIMUM");
					return qs;
				}
			case OptymalizationType::MAXIMUM:
				{
					std::stringstream tmpSS;
					QString qs = tr("   Kind of extremum: MAXIMUM");
					return qs;
				}
			default:
				{
					return 0;
				}
		}
}

QString MainWindow::_getWeights()
{
		std::stringstream tmpSS;
	    tmpSS << "Weights: \n";
	    int index =0;
	    for(int i =0 ; i<dataSettings().nrOfLayers;i++)
	    {
	    	tmpSS<<"   Layer nr. "<<i<<"\n";
	    	for(int j=0 ; j<dataSettings().layersSize[i];j++)
	    	{
	    		tmpSS<<"      Neuron nr. "<<j<<" : ";
	    		if(i==0)
	    		{
	    			tmpSS<<"   { ";
					for(int k=0 ; k<dataSettings().nrInputData-1;k++)
					{
						tmpSS<<dataSettings().weights[index]<<", ";
						++index;
					}
					tmpSS<<dataSettings().weights[index]<<" }\n";
					++index;
				}
	    		else
	    		{
	    			tmpSS<<"   { ";
	    			for(int k=0 ; k<(dataSettings().layersSize[i-1]-1);k++)
	    			{

	    				tmpSS<<dataSettings().weights[index]<<", ";
						++index;
	    			}
	    			tmpSS<<dataSettings().weights[index]<<" }\n";
	    			++index;
	    		}
	    	}
	    	tmpSS<<"\n";
	    }
		QString qs(tmpSS.str().c_str());
		return qs;
}

void MainWindow::saveSettingsToFile(QString fileName, bool weights)
{
	WriteDataFile wdf = WriteDataFile(dataSettings().PROGRAM_SETTINGS_FILE_NAME);
	wdf.saveSettingsToFile( dataSettings(), false);
}


//ustawić zmienne globalne dotyczące ścieżek i nazw plików!!!!!!!!!!!!
void MainWindow::readSettingsFromFile()
{
	if ( ReadDataFile::isFileExist(dataSettings().MAIN_FOLDER_NAME +
			dataSettings().PROGRAM_SETTINGS_FILE_NAME ))
	{
		ReadDataFile rdf = ReadDataFile(dataSettings().MAIN_FOLDER_NAME +
				dataSettings().PROGRAM_SETTINGS_FILE_NAME);

		rdf.loadSettingsFromFile(dataSettings(), false);
	}
	else
	{
		dataSettings().setDeafultValues();
	}
}


void MainWindow::initializeNeuralNetworkObjects()
{
	if ( neuralNetwork != NULL )
		delete neuralNetwork;

	if ( evolutionaryAlgorithm != NULL )
		delete evolutionaryAlgorithm;

	neuralNetwork = NeuralNetwork::getInstance( dataSettings() );

	Individual::setBegin( dataSettings().minWeightRange );
	Individual::setEnd( dataSettings().maxWeightRange );

	if ( dataSettings().EvolAlgorithm == EvolAlgorithm::DE )
	{
		evolutionaryAlgorithm = DifferentialEvolution::getInstance( dataSettings() );
	}
	else if ( dataSettings().EvolAlgorithm == EvolAlgorithm::SOMA )
	{
		evolutionaryAlgorithm = SOMA::getInstance( dataSettings() );
	}
}

QString MainWindow::doubletostring(double tab[], int size)
{
	QString result;
	QString tmp;

	for(int i = 0; i < size; i++)
	{
		result += tmp.setNum(tab[i]);
		result += ", ";
	}
	return result;
}

QString MainWindow::doubletostring(int tab[], int size)
{
	QString result;
	QString tmp;

	for(int i = 0; i < size; i++)
	{
		result += tmp.setNum(tab[i]);
		result += ", ";
	}
	return result;
}

int MainWindow::_getWeightsNr()
{
	int tmp=0;
	for(int i =0;i<dataSettings().nrOfLayers;i++)
	{
		if(i==0)
		{
			tmp += dataSettings().layersSize[i]*dataSettings().nrInputData;
		}
		else
		{
			tmp+= dataSettings().layersSize[i]*dataSettings().layersSize[i-1];
		}
	}
	return tmp;
}

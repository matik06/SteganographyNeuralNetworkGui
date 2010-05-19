/*
 * WriteDataFile.cpp
 *
 *  Created on: 2010-05-14
 *      Author: Mateusz Lubański
 */

#include "WriteDataFile.h"


const QString WriteDataFile::MAIN_FOLDER_NAME = "data";


/******************************************************************************
						constructors and destructors
 *****************************************************************************/


WriteDataFile::WriteDataFile( QString fileName ):
	_WEIGHT_PRECISION(5)
{
	_file = new QFile( QDir::currentPath() + QDir::separator() + MAIN_FOLDER_NAME +
			QDir::separator() + fileName);

	_file->open(QIODevice::WriteOnly);
}


WriteDataFile::~WriteDataFile()
{
	if ( _file->isOpen() )
	{
		this->_file->close();
		delete _file;
	}
}


/******************************************************************************
			 					public methods
 *****************************************************************************/


void WriteDataFile::createMainFoder(QString folderName)
{
	QDir dir;
	dir.mkdir(QDir::currentPath() + QDir::separator() + folderName);
}

void WriteDataFile::createMainFolder()
{
	QDir dir;
	dir.mkdir(QDir::currentPath() + QDir::separator() + MAIN_FOLDER_NAME);
}


bool WriteDataFile::saveWeightsToTxtFile( int iNrLayer, int iNrNeurons [],
		int iNrInputWeights, double *** aWeights )
{
	QTextStream ts(_file);

	int * aNrWeights = new int[iNrLayer];
	aNrWeights[0] = iNrInputWeights;

	for (int i = 1; i < iNrLayer; ++i) {
		aNrWeights[i] = iNrNeurons[i-1];
	}

	ts << '{';
	for (int i = 0; i < iNrLayer; ++i)
	{
		ts << '{';
		for (int j = 0; j < iNrNeurons[i]; ++j)
		{
			ts << '{';
			for (int k = 0; k < aNrWeights[i]; ++k)
			{

				ts << QString::number(aWeights[i][j][k], 'f', _WEIGHT_PRECISION);
				writeComa(ts, k, aNrWeights[i]);
			}
			ts << '}';
			writeComa(ts, j, iNrNeurons[i]);
		}
		ts << '}';
		writeComa(ts, i, iNrLayer);
	}
	ts << '}';

	return true;
}


void WriteDataFile::saveSettingsToFile( Singleton & settings, bool neuralNetworkWeights )
{
	QDataStream ds(_file);
	ds.setVersion(QDataStream::Qt_4_5);

	//saving neural network settings
	ds << settings.nrOfLayers;
	saveArray( ds, settings.layersSize, settings.nrOfLayers );
	ds << settings.nrInputData;
	saveArray( ds, settings.neuronType, settings.nrOfLayers );
	saveArray( ds, settings.alfa, settings.nrOfLayers );
	saveArray( ds, settings.beta, settings.nrOfLayers );
	ds << settings.EvolAlgorithm;
	ds << settings.oType;

	//saving SOMA settings
	ds << settings.step;
	ds << settings.pathLength;
	ds << settings.PRT;
	ds << settings.accError;
	ds << settings.migrations;
	ds << settings.popSizeSoma;

	//saving DE settings
	ds << settings.crossover;
	ds << settings.mutationConstant;
	ds << settings.iterations;
	ds << settings.popSizeDE;

	//saving neural network weights
	if ( neuralNetworkWeights )
	{
		saveArray( ds, settings.weights, settings.getNrWeights() );
	}
}


void WriteDataFile::saveRecognitionStatistics( double ** aData, int iNrData,
		int correct, int incorrect)
{
	QTextStream ts(_file);

	ts << "incorrect sets: " << incorrect << "\n";
	ts << " correct sets: " << correct << "\n\n";

	ts << "{";
	for (int i = 0; i < correct; ++i)
	{
		ts << "{";
		for (int j = 0; j < iNrData; ++j) {
			ts << aData[i][j];
			writeComa(ts, j, iNrData);
		}
		ts << "}";
		writeComa(ts, i, correct);
	}
	ts << "}";
}


/******************************************************************************
			 					private methods
 *****************************************************************************/


void WriteDataFile::writeComa(QTextStream & ts, int index, int max)
{
	if ( index < --max ) {
		ts << ", ";
	}
}


template <class T>
void WriteDataFile::saveArray( QDataStream & ds, T * array, int size )
{
	for (int i = 0; i < size; ++i)
	{
		ds << array[i];
	}
}

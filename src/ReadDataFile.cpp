/*
 * ReadDataFile.cpp
 *
 *  Created on: 2010-05-14
 *      Author: matik
 */

#include "ReadDataFile.h"

/******************************************************************************
						constructors and destructors
 *****************************************************************************/

ReadDataFile::ReadDataFile( QString file )
{
	if ( QFile::exists( file ) ) {

		_file = new QFile( file );
		_file->open( QIODevice::ReadOnly );

	} else {

		_file = NULL;
	}
}


ReadDataFile::~ReadDataFile()
{
	if ( _file != NULL )
	{
		if ( _file->isOpen() )
		{
			this->_file->close();
			delete _file;
		}
	}
}


/******************************************************************************
			 					public methods
 *****************************************************************************/


int ReadDataFile::loadFileWithInputs( int iNrInput, int iNrOutput,
		double **& aInputData, double **& aOutputData )
{
	if ( _file == NULL )
	{
		return false;	//if file doesn't exits return false
	}

	QTextStream ts( _file );
	int iNrDataSet = countNrSets( ts );	//get number of data sets in file

	if ( iNrDataSet < 2 )
	{
		return false;	//in file have to more than 2 data sets
	}

	initializeArray( aInputData, iNrDataSet, iNrInput );
	initializeArray( aOutputData, iNrDataSet, iNrOutput );

	readChar( ts, '{' );

	for (int i = 0; i < iNrDataSet; ++i)
	{
		readChar(ts, '{');

		readData( ts, aInputData[i], iNrInput );	//get input data set
		readChar( ts, ',' );
		readData( ts, aOutputData[i], iNrOutput );	//get output data set

		readChar( ts, '}' );
	}

	return iNrDataSet;
}


void ReadDataFile::loadSettingsFromFile( Singleton & settings, bool neuralNetworkWeights )
{
	QDataStream ds(_file);
	ds.setVersion(QDataStream::Qt_4_5);
	int temp;

	//loading neural network settings
	ds >> settings.nrOfLayers;
	loadArray( ds, settings.layersSize, settings.nrOfLayers );
	ds >> settings.nrInputData;

	loadEnumArray( ds, settings.neuronType, settings.nrOfLayers);

	loadArray( ds, settings.alfa, settings.nrOfLayers );
	loadArray( ds, settings.beta, settings.nrOfLayers );
	ds >> temp;
	settings.EvolAlgorithm = (EvolAlgorithm::Enum)temp;
	ds >> temp;
	settings.oType = (OptymalizationType::Enum)temp;

	//loading SOMA settings
	ds >> settings.step;
	ds >> settings.pathLength;
	ds >> settings.PRT;
	ds >> settings.accError;
	ds >> settings.migrations;
	ds >> settings.popSizeSoma;

	//loading DE settings
	ds >> settings.crossover;
	ds >> settings.mutationConstant;
	ds >> settings.iterations;
	ds >> settings.popSizeDE;

//	bool isWeights;
//	ds >> settings.isWeights;

	//loading neural network weights
	if ( neuralNetworkWeights )
	{
		loadArray( ds, settings.weights, settings.getNrWeights() );
		settings.weightsNumber = settings.getNrWeights();
	}
	else
	{
		settings.weightsNumber =0;

		if ( settings.weights != NULL )
		{
			settings.weights = NULL;
		}
	}

}


bool ReadDataFile::isFileExist(QString file)
{
	return QFile::exists(file);
}


/******************************************************************************
			 					private methods
 *****************************************************************************/


void ReadDataFile::readData( QTextStream & ts, double * aData, int iDataSize )
{

	readChar( ts, '{' );

	for (int i = 0; i < iDataSize - 1; ++i)
	{
		ts >> aData[i];		//reading single number from set
		readChar( ts, ',' );
	}

	ts >> aData[iDataSize-1];	//reading last number from set

	readChar( ts, '}' );
}


void ReadDataFile::readChar( QTextStream & ts, char c)
{
	QChar temp;

	do
	{
		ts >> temp;
	}
	while ( temp != c);
}


template <class T>
void ReadDataFile::initializeArray(T *& aData, int size)
{
	if ( aData != NULL )
	{
		delete aData;
	}

	aData = new T[size];
}


void ReadDataFile::initializeArray( double **& aData, int iNrDataSet, int iNrData )
{
	aData = new double*[iNrDataSet];

	for (int i = 0; i < iNrDataSet; ++i) {
		aData[i] = new double[iNrData];
	}
}


int ReadDataFile::countNrSets( QTextStream & ts )
{
	QString s = ts.readAll();	//reading all data from file
	int result = s.count( '{' );	//counting number of '{' in file

	result -= 1;
	result /= 3;

	ts.seek( 0 );	//set QTextStream data at begining

	return result;
}


template <class T>
void ReadDataFile::loadArray( QDataStream & ds, T *& aData, int size)
{
	initializeArray(aData, size);

	for (int i = 0; i < size; ++i)
	{
		ds >> aData[i];
	}
}


template <class T>
void ReadDataFile::loadEnumArray( QDataStream & ds, T *& array, int size)
{
	initializeArray(array, size);
	int temp;

	for (int i = 0; i < size; ++i)
	{
		ds >> temp;
		array[i] = (KindOfNeuron::Enum)temp;
	}
}

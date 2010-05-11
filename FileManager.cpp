/*
 * FileManager.cpp
 *
 *  Created on: 2010-05-07
 *      Author: Mateusz Lubański
 */

#include "FileManager.h"

QString FileManager::_sMainFolderName = "data";

FileManager::FileManager(QString fileName) {

	createMainFoder(_sMainFolderName);

	_file = new QFile( QDir::currentPath() + QDir::separator() + _sMainFolderName +
			QDir::separator() + fileName);

	_file->open(QIODevice::WriteOnly);
}

FileManager::FileManager(QString path, QString fileName){

	if ( QFile::exists(path + fileName) ) {
		_file = new QFile(path + fileName);
		_file->open(QIODevice::ReadOnly);
	} else {
		_file = NULL;
	}
}

FileManager::~FileManager() {
	//if file is opened - close it
	if (this->_file->isOpen()) {
		this->_file->close();
	}
}


//dla jednego zestawy danych nie działa dobrze!!!!!!!!!!!!!!!!
bool FileManager::readData(int iNrInput, int iNrOutput, double **& aInputData,
		double **& aOutputData)
{
	if (this->_file == NULL) {
		return false;	//if file doesn't exits return false
	}

	QTextStream ts(_file);

	//reading number of sets in file
	int iNrDataSet = countNrSets( ts );

	if (iNrDataSet < 2) {
		return false;
	}

	//initializing arrrays
	initializeArray(aInputData, iNrDataSet, iNrInput);
	initializeArray(aOutputData, iNrDataSet, iNrOutput);

	//reading data sets from file
	readChar(ts, '{');

	for (int i = 0; i < iNrDataSet; ++i) {

		readChar(ts, '{');

		readData(ts, aInputData[i], iNrInput);	//get input data set
		readChar(ts, ',');
		readData(ts, aOutputData[i], iNrOutput);	//get output data set

		readChar(ts, '}');
	}

	return true;
}


bool FileManager::createFileWithWeights(int iNrLayer, int iNrNeurons [],
		int iNrInputWeights, double *** aWeights) {

	if (_file->isReadable()) {
		return false;
	}

	QTextStream ts(_file);

	//create array with number of weights for neurons in every layer
	int * aNrWeights = new int[iNrLayer];
	aNrWeights[0] = iNrInputWeights;

	for (int i = 1; i < iNrLayer; ++i) {
		aNrWeights[i] = iNrNeurons[i-1];
	}

	//saving data to file
	ts << '{';
	for (int i = 0; i < iNrLayer; ++i) {
		ts << '{';
		for (int j = 0; j < iNrNeurons[i]; ++j) {
			ts << '{';
			for (int k = 0; k < aNrWeights[i]; ++k) {

				ts << QString::number(aWeights[i][j][k], 'f', 5);
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

/******************************************************************************
			 *					private methods
 *****************************************************************************/

void FileManager::createMainFoder(QString folderName)
{
	QDir dir;
	dir.mkdir(QDir::currentPath() + QDir::separator() + folderName);
}


void FileManager::readData( QTextStream & ts, double * aData, int iDataSize )
{

	readChar(ts, '{');

	for (int i = 0; i < iDataSize - 1; ++i) {
		ts >> aData[i];			//reading single number from set
		readChar(ts, ',');
	}

	ts >> aData[iDataSize-1];	//reading last number from set

	readChar(ts, '}');
}

void FileManager::readChar( QTextStream & ts, char c)
{
	QChar temp;

	do {
		ts >> temp;
	} while ( temp != c);
}

void FileManager::initializeArray(double **& aData, int iNrDataSet, int iNrData)
{
	aData = new double*[iNrDataSet];

	for (int i = 0; i < iNrDataSet; ++i) {
		aData[i] = new double[iNrData];
	}
}

void FileManager::writeComa(QTextStream & ts, int index, int max)
{
	if ( index < --max) {
		ts << ", ";
	}
}

int FileManager::countNrSets( QTextStream & ts )
{
	int result = ts.readAll().count('{');
	result -= 1;
	result /= 3;

	ts.seek(0);
	return result;
}

/*
 * Singleton.cpp
 *
 *  Created on: 2009-11-29
 *      Author: matik
 */

#include "Singleton.h"

Singleton::Singleton():
	PROGRAM_SETTINGS_FILE_NAME("settings.ns"),
	MAIN_FOLDER_NAME(QString("data") + QDir::separator())
{
	weights = NULL;
	layersSize = NULL;
	alfa = NULL;
	beta = NULL;
}

Singleton::~Singleton()
{
	delete [] weights;
	delete [] layersSize;
	delete [] alfa;
	delete [] beta;
}

int Singleton::getNrWeights()
{
	int result;

	//get number of weights in first layer
	result = layersSize[0] * nrInputData;

	for (int i = 1; i < nrOfLayers; ++i)
	{
		result += layersSize[i] * layersSize[i-1];
	}

	return result;
}

int Singleton::getOutputLayerSize()
{
	return layersSize[nrOfLayers -1];
}

Singleton & dataSettings()
{
	static Singleton dataSettings;
	return dataSettings;
}


template <class T>
void Singleton::initializeArray(T *& array, int size)
{
	if ( array != NULL ) {
		delete array;
	}

	array = new T[size];
}


void Singleton::setDeafultValues()
{
	//neural network

	nrOfLayers = 2;

	initializeArray( layersSize, nrOfLayers );
	initializeArray( alfa, nrOfLayers );
	initializeArray( beta, nrOfLayers );
	initializeArray( neuronType, nrOfLayers );

	for (int i = 0; i < nrOfLayers; ++i) {
		layersSize[i] = 10;
		alfa[i] = 0.5;
		beta[i] = 0.5;
		neuronType[i] = KindOfNeuron::LINEAR;
	}

	nrInputData = 5;
	oType = OptymalizationType::MINIMIM;
	EvolAlgorithm = EvolAlgorithm::SOMA;

	//soma
	migrations = 25;
	popSizeSoma = 10;
	step = 0.3;
	pathLength = 3.0;
	PRT = 0.4;
	accError = -1;

	//de
	iterations = 25;
	popSizeDE = 10;
	mutationConstant = 0.8;
	crossover = 0.25;

	//weights
//	isWeights = false;
	weightsNumber = 0;
}


void Singleton::setWeights( const double * aWeights, int iSize )
{
	if ( weights != NULL )
		delete weights;

	weightsNumber = iSize;
	weights = new double[iSize];

	for (int i = 0; i < iSize; ++i)
	{
		weights[i] = aWeights[i];
	}
}

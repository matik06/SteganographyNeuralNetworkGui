/*
 * NeuralNetwork.cpp
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#include "NeuralNetwork.h"



NeuralNetwork::NeuralNetwork( int iNrLayers, int aLayersSize[],int iNrInputData,
							  KindOfNeuron::Enum * neuronType, double aAlfa[], double aBeta[]):
	_iNrLayers( iNrLayers ),
	_iOutputLayerSize( aLayersSize[ iNrLayers-1 ] )
{
	//creating and initializing array with size all layers
	this->aLayersSize = new int[this->_iNrLayers];
	for(int i = 0; i < this->_iNrLayers; i++)
	{
		this->aLayersSize[i] = aLayersSize[i];
	}


	//creating and initializing array of Layers
	this->_aLayers = new Layer*[this->_iNrLayers];

	//set first layer
	this->_aLayers[0] = new Layer( this->aLayersSize[0], iNrInputData,
			   neuronType[0], aAlfa[0], aBeta[0]);
	//set rest of layers
	for(int i = 1; i < this->_iNrLayers; i++)
	{
		//every next layer have neurons with number of input data (weights)
		//equal number of neurons in layer one before
		int iNrNeuronsInLayer = this->aLayersSize[i-1];
		this->_aLayers[i] = new Layer( this->aLayersSize[i], iNrNeuronsInLayer,
									   neuronType[i], aAlfa[i], aBeta[i]);
	}

	this->_iNrPaterns = 0;
	this->_aPatterns = 0;

	int dimensions = 0;
	dimensions = aLayersSize[0] * iNrInputData;

	for(int i = 1; i < iNrLayers; i++)
	{
		dimensions += aLayersSize[i] * aLayersSize[i-1];
	}

	Individual::setDimensions(dimensions);
}


NeuralNetwork::~NeuralNetwork()
{
	//deleting pointers for layers
	for(int i = 0; i < this->_iNrLayers; i++)
	{
		delete this->_aLayers[i];
	}

	//deleting array with pointers
	delete [] this->_aLayers;
}


Layer & NeuralNetwork::operator []( unsigned int index)
{
	return *this->_aLayers[index];
}


void NeuralNetwork::setWeights( double aWeights[] )
{
	int n = 0;
	int nrWeights = 0;

	for(int i = 0; i < this->_iNrLayers; i++)
	{
		//number weights in all neurons in i-layer
		nrWeights = this->operator [](i).getNrInputData();

		for(int j = 0; j < this->aLayersSize[i]; j++)
		{
			for(int k = 0; k < nrWeights; k++)
			{
				// this means the same (*this->_aLayers[i])[j][k] = aWeights[n]; than:
				this->operator [](i)[j][k] = aWeights[n];
				n++;
			}
		}
	}
}


void NeuralNetwork::setWeights( double dValue )
{
	int nrWeights = 0;

	for(int i = 0; i < this->_iNrLayers; i++)
	{
		//number weights in all neurons in i-layer
		nrWeights = this->operator [](i).getNrInputData();

		for(int j = 0; j < this->aLayersSize[i]; j++)
		{
			for(int k = 0; k < nrWeights; k++)
			{
				// this means the same (*this->_aLayers[i])[j][k] = aWeights[n]; than:
				this->operator [](i)[j][k] = dValue;
			}
		}
	}
}

double * NeuralNetwork::getNeuralNetworkOutput( double aInputSignal[] )
{
	// variables necessary for storing results
	double * aOutput;
	double * aOutputTmp;

	//get layer output signal from first layer
	aOutput = this->operator [](0).getLayerOutput( aInputSignal );

	//if neural network has more than 1 layer
	if(this->_iNrLayers > 1)
	{
		for(int i = 1; i < this->_iNrLayers; i++)
		{
			//get output signal from next layer (sending to function output signal
			//from layer one before)
			aOutputTmp = this->operator [](i).getLayerOutput( aOutput );

			//deleting data from  aOutput and copy into this variable data
			//from aOutputTmp - current output signal from i-layer
			delete [] aOutput;
			aOutput = new double[ this->operator [](i).getLayerSize() ];

			for(int j = 0; j < this->operator [](i).getLayerSize(); j++)
			{
				aOutput[j] = aOutputTmp[j];
			}

			delete [] aOutputTmp;
		}
	}

	return aOutput;
}

void NeuralNetwork::setPatterns( double ** aPatterns, int nrPatterns )
{
	//deleting old array with patterns
	if( this->_aPatterns != 0 )
	{
		for(int i = 0; i < _iNrPaterns; i++)
		{
			delete [] _aPatterns[i];
		}
		delete [] _aPatterns;
	}

	//creating and initializing array with patterns
	this->_aPatterns = new double*[nrPatterns];
	for(int i = 0; i < nrPatterns; i++)
	{
		this->_aPatterns[i] = new double[this->_iOutputLayerSize];
		for(int j = 0; j < this->_iOutputLayerSize; j++)
		{
			this->_aPatterns[i][j] = aPatterns[i][j];
		}
	}
}

double NeuralNetwork::getCostValue( double aWeights[], double ** aInputData )
{
	double * output;//
	double * tmpCV = new double[this->_iNrPaterns];
	double result = 0;

	//set weights in neural network from best individual parameters
	this->setWeights( aWeights );

	for(int i = 0; i < this->_iNrPaterns; i++)
	{
		output = new double[this->_iOutputLayerSize];

		//counting output for one set of data
		output = this->getNeuralNetworkOutput( aInputData[i] );

		//counting cost value for single set of data
		for(int j = 0; j < this->_iOutputLayerSize; j++)
		{
			//tmpCV[j] = |p1-y1|+|p2-y2|+|p3-y3|...
			tmpCV[j] += fabs( this->_aPatterns[i][j] - output[j] );
		}

		delete[] output;
	}

	//counting main cost value
	for(int i = 0; i < this->_iNrPaterns; i++)
	{
		result += tmpCV[i];
	}
	delete [] tmpCV;

	return result;
}

double * NeuralNetwork::getWeights()
{
	//i am lazy today
	//i have to finish it later
	//actually i don't need this method
}


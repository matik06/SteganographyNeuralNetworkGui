/*
 * Neuron.cpp
 *
 *  Created on: 2009-10-21
 *      Author: matik
 */

#include "Neuron.h"


/****************************************
 *		  	public methods:				*
 ****************************************/


Neuron::Neuron( int iNrInputData):
	_iNrOfInputData(iNrInputData)
{
	this->_aWeights = new double[ this->_iNrOfInputData ];

	/*
	 * initialization all values in array with 0
	 * in case if someone will try read it before initialization with
	 * random data <a,b>
	*/
	for(int i = 0; i < _iNrOfInputData; i++)
	{
		this->_aWeights[i] = 0;
	}
}

Neuron::~Neuron()
{
	delete [] _aWeights;
}

double & Neuron::operator [](unsigned int index)
{
	return this->_aWeights[index];
}

void Neuron::setWeights( double aWeights[] )
{
	for(int i = 0; i < _iNrOfInputData; i++)
	{
		this->_aWeights[i] = aWeights[i];
	}
}

int Neuron::getNrWeights()
{
	return _iNrOfInputData;
}



/****************************************
 *		  	private methods:				*
 ****************************************/

double Neuron::_sumator( double aInputData[] )
{
	double dResult = 0;

	for(int i = 0; i < this->_iNrOfInputData; i++)
	{
		dResult += this->_aWeights[i] * aInputData[i];
	}

	return dResult;
}



/*
 * SigmoidalNeuron.cpp
 *
 *  Created on: 2009-10-21
 *      Author: matik
 */

#include "SigmoidalNeuron.h"


SigmoidalNeuron::SigmoidalNeuron( int iNrInputDta, double dBeta ):
		Neuron( iNrInputDta ), _dBeta(dBeta)
{

}

SigmoidalNeuron::~SigmoidalNeuron()
{

}

double SigmoidalNeuron::derivativeOutput( double dInpudData[] )
{
	//f(x)
	double output = this->output(dInpudData);
	//f '(x) = beta*[1-f(x)]*f(x)
	double result = this->_dBeta * (1 - output) * output;

	return result;
}

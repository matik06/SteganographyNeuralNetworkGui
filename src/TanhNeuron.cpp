/*
 * TanhNeuron.cpp
 *
 *  Created on: 2009-10-21
 *      Author: matik
 */

#include "TanhNeuron.h"
#include <cmath>

TanhNeuron::TanhNeuron( int iNrInputData , double dAlfa):
		Neuron(iNrInputData), _dAlfa(dAlfa)
{

}

TanhNeuron::~TanhNeuron()
{

}

double TanhNeuron::output( double aInputData[] )
{
	double x = this->_sumator(aInputData);

	//y=(1-exp(-alfa*x))/(1+exp(-alfa*x))
	return ( 1-exp(-_dAlfa * x) ) / ( 1 + exp(-_dAlfa * x) );
}

double TanhNeuron::derivativeOutput( double dInpudData[] )
{
	//f(x)
	double output = this->output(dInpudData);

	//f '(x) = alfa[1-f^2(x)]
	return ( _dAlfa * (1 - output * output) );
}

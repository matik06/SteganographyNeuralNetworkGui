/*
 * LinearNeuron.cpp
 *
 *  Created on: 2010-05-12
 *      Author: matik
 */

#include "LinearNeuron.h"

LinearNeuron::LinearNeuron(int iNrInputData, double dAlfa):
	Neuron(iNrInputData), _dParam(dAlfa)
{

}

LinearNeuron::~LinearNeuron()
{

}


double LinearNeuron::output( double aInputData[] )
{
	double x = this->_sumator(aInputData);
	return x * _dParam;
}

double LinearNeuron::derivativeOutput( double dInpudData[] )
{
	return 0;
}

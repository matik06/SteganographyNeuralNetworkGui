/*
 * SigmoidalBPNeuron.cpp
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#include "SigmoidalBPNeuron.h"
#include <cmath>

SigmoidalBPNeuron::SigmoidalBPNeuron( int iNrInputData, double dBeta ):
	SigmoidalNeuron(iNrInputData, dBeta)
{

}

SigmoidalBPNeuron::~SigmoidalBPNeuron()
{

}

double SigmoidalBPNeuron::output( double aInputData[] )
{
	// x = result of multiplicity weights by input signal
	double x = this->_sumator( aInputData );

	//y=2/(1+exp(-beta*suma_w))-1
	return 2 / (1 + exp(-_dBeta * x)) - 1;
}

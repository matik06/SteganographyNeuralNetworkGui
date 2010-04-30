/*
 * SigmoidalUPNeuron.cpp
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#include "SigmoidalUPNeuron.h"
#include "SigmoidalNeuron.h"
#include <cmath>

SigmoidalUPNeuron::SigmoidalUPNeuron( int iNrInputData, double dBeta ):
	SigmoidalNeuron( iNrInputData, dBeta )
{

}

SigmoidalUPNeuron::~SigmoidalUPNeuron()
{

}

double SigmoidalUPNeuron::output( double aInputData[] )
{
	// x = result of multiplicity weights by input signal
	double x = this->_sumator( aInputData );

	//y=1/(1+exp(-beta*x))
	return 1 / (1+exp(-_dBeta * x));
}

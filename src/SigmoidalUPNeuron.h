/*
 * SigmoidalUPNeuron.h
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#ifndef SIGMOIDALUPNEURON_H_
#define SIGMOIDALUPNEURON_H_

#include "SigmoidalNeuron.h"

class SigmoidalUPNeuron: public SigmoidalNeuron
{
public:

	/**
	 * constructor
	 *
	 * @param: int iNrInputData - number of input data (weights)
	 * @param: double dBeta - beta parameter for activation function
	 */
	SigmoidalUPNeuron( int iNrInputData, double dBeta = 0.5 );
	~SigmoidalUPNeuron();


	/**
	 * return neuron output
	 *
	 * @param: double aInputData[] - input signal for neuron
	 * @return: double - neuron output
	 */
	double output( double inputData[] );
};

#endif /* SIGMOIDALUPNEURON_H_ */

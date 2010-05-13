/*
 * SigmoidalBPNeuron.h
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#ifndef SIGMOIDALBPNEURON_H_
#define SIGMOIDALBPNEURON_H_

#include "SigmoidalNeuron.h"

class SigmoidalBPNeuron: public SigmoidalNeuron
{
public:

	/**
	 * constructor
	 *
	 * @param: int iNrInputData - number of input data (weights)
	 * @param: double dBeta - parameter for activation function
	 */
	SigmoidalBPNeuron( int iNrInputData, double dBeta = 0.5 );
	~SigmoidalBPNeuron();


	/**
	 * return neuron output
	 *
	 * @param: double aInputData[] - input signal for neuron
	 * @return: double - neuron output
	 */
	double output( double inputData[] );
};

#endif /* SIGMOIDALBPNEURON_H_ */

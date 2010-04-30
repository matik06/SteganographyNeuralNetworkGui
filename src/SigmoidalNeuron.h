/*
 * SigmoidalNeuron.h
 *
 *  Created on: 2009-10-21
 *      Author: matik
 */

#ifndef SIGMOIDALNEURON_H_
#define SIGMOIDALNEURON_H_

#include "Neuron.h"
#include <cmath>

class SigmoidalNeuron: public Neuron
{
protected:

	double _dBeta;

public:

	/**
	 * constructor
	 *
	 * @param: int iNrInputData - number of input data (weights)
	 * @param: double dBeta - parameter for activation function
	 */
	SigmoidalNeuron( int iNrInputData , double dBeta);
	~SigmoidalNeuron();


	/**
	 * return neuron output
	 *
	 * @param: double aInputData[] - input signal for neuron
	 * @return: double - neuron output
	 */
	virtual double output( double inputData[] ) = 0;

	/**
	 * return derivative of neuron output
	 *
	 * @param: double aInputData[]
	 * @return: double - derivative of neuron output
	 */
	double derivativeOutput( double inputData[] );
};

#endif /* SIGMOIDALNEURON_H_ */

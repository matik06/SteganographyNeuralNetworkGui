/*
 * TanhNeuron.h
 *
 *  Created on: 2009-10-21
 *      Author: matik
 */

#ifndef TANHNEURON_H_
#define TANHNEURON_H_

#include "Neuron.h"

class TanhNeuron: public Neuron
{
protected:

	//parameter used in activation function (default value = 0.5)
	double _dAlfa;

public:

	/**
	 * constructor
	 *
	 * @param: int iNrInputData - number of input data (weights)
	 * @param: double dAlfa - parameter for activation function
	 */
	TanhNeuron( int iNrInputData, double dAlfa = 0.5 );
	~TanhNeuron();

	/**
	 * return neuron output
	 *
	 * @param: double aInputData[] - input signal for neuron
	 * @return: double - neuron output
	 */
	double output( double inputData[] );

	/**
	 * return derivative of neuron output
	 *
	 * @param: double aInputData[]
	 * @return: double - derivative of neuron output
	 */
	double derivativeOutput( double inputData[] );
};

#endif /* TANHNEURON_H_ */

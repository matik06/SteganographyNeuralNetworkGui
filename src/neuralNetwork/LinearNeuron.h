/*
 * LinearNeuron.h
 *
 *  Created on: 2010-05-12
 *      Author: matik
 */

#ifndef LINEARNEURON_H_
#define LINEARNEURON_H_

#include "Neuron.h"

class LinearNeuron: public Neuron
{
protected:
	double _dParam;

public:

	/**
	 * constructor
	 *
	 * @param: int iNrInputData - number of input data (weights)
	 * @param: double dParam - parameter for activation function
	 */
	LinearNeuron(int iNrInputData, double dParam = 1);
	virtual ~LinearNeuron();


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

#endif /* LINEARNEURON_H_ */

/*
 * Layer.h
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#ifndef LAYER_H_
#define LAYER_H_

#include "Neuron.h"
#include "TanhNeuron.h"
#include "SigmoidalUPNeuron.h"
#include "SigmoidalBPNeuron.h"

#include "EnumTypes.h"

class Layer
{
protected:

	//number of neurons in layer
	int _iNrNeurons;
	//array of pointers to Neuron object
	Neuron ** _aNeurons;


public:

	/**
	 * Constructor - single layer defined by parameters:
	 *
	 * @param: int iNeuronNumbers - number of neurons in layer
	 * @param: int iNrInputData - number of weights (input signal) in neurons in layer
	 * @param: KindOfNeuron::Enum neuronType - type of neurons(different activation function)
	 * @param: double dAlfa - alfa parameter (needed for TanhNeurons)
	 * @param: double dBeta - beta parameter (needed for SigmoidalNeurons)
	 */
	Layer( int iNeuronNumbers, int iNrInputData, KindOfNeuron::Enum neuronType,
			  double dAlfa = 0.5,  double dBeta = 0.5 );
	~Layer();

	/**
	 * overloaded operator [] - using for acces for n-neuron
	 *
	 * @param: int - number of neuron
	 *
	 * @return: Neuron - single neuron
	 */
	Neuron & operator[](unsigned int index);

	/**
	 * return layer output (y[])
	 *
	 * @param: double aInputData[] - input signal
	 * @return: double[] - layer output
	 */
	double * getLayerOutput( double aInputData[] );

	/**
	 * return numbers of neurons in layer
	 *
	 * @return: int - number of neurons in layer
	 */
	int getLayerSize();

	/**
	 * return number of input data (number of weights in neurons)
	 *
	 * @return: int - number of input data
	 */
	int getNrInputData();

protected:

	/**
	 * initialization array of pointers to Neuron objects
	 * @param: int iNrInputData - number of weights (input signal) in neurons in layer
	 * @param: KindOfNeuron::Enum neuronType - neuron type
	 * @param: double dAlfa - parameter for activation function (Tannh f)
	 * @param: double dBeta - parameter for activation function (Sigmoidal f)
	 *
	 * @return: void
	 */
	void _setNeurons( KindOfNeuron::Enum neuronType, int iNrInputData,
					  double dAlfa = 0.5, double dBeta = 0.5);
};

#endif /* LAYER_H_ */

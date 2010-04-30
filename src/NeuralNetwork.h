/*
 * NeuralNetwork.h
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#ifndef NEURALNETWORK_H_
#define NEURALNETWORK_H_

#include <cmath>
#include "Individual.h"
#include "Layer.h"
#include "EnumTypes.h"
//#include "EvolutionaryAlgorithm.h"


class NeuralNetwork
{
protected:

	//number of layers in neural network
	int _iNrLayers;
	//size of every layer in neural network
	int * aLayersSize;
	//array with layers in neural network
	Layer ** _aLayers;
	//number of neurons (layer output) in last layer (output layer)
	int _iOutputLayerSize;
	//patterns
	double ** _aPatterns;
	//number of paterns
	int _iNrPaterns;

public:

	/**
	 * Constructor - neural network defined by parameters:
	 *
	 * @param: int iNrLayers - number of layers i neural network
	 * @param: int aSizeLayers[] - array with numbers of neurons in every layer
	 * @param: int iNrInputData - number of weights (input signal) in every neuron
	 * @param: KindOfNeuron::Enum neuronType - type of neurons(different activation function)
	 * @param: double dMaxWeightsValue - variable necessary for counting the patterns
	 * @param: double * aAlfa - alfa parameters (needed for TanhNeurons)
	 * @param: double * aBeta - beta parameters (needed for SigmoidalNeurons)
	 */
	NeuralNetwork( int iNrLayers, int aSizeLayers[], int iNrInputData,
				   KindOfNeuron::Enum * neuronType,
				   double aAlfa[], double aBeta[] );
	~NeuralNetwork();

	/**
	 * set all weights in neural network
	 *
	 * @param: double aWeights[] - array with weights
	 * @return: void
	 */
	void setWeights( double aWeights[] );

	/**
	 * set all weights in neural network with the same value
	 * max weight value - necessary for counting patterns
	 *
	 * @param: double dValue - value for all weights
	 * @return: void
	 */
	void setWeights( double dValue );

	/*
	 * create patterns (necessary for counting CostValue in Individual)
	 *
	 *
	 * @param: double aPatterns[] - array with patterns
	 * @return: void
	 */
	void setPatterns( double ** aPatterns, int nrPatterns );

	/**
	 * return neural network output (vector)
	 *
	 * @param: double aInputSignal[] - input signal
	 * @return: neural network output
	 */
	double * getNeuralNetworkOutput( double aInptSignal[] );

	/**
	 *	return cost value for individual
	 *
	 *	@param Individual individual
	 */
	double getCostValue( double dWeights[], double ** dInputData );


	double * getWeights();
	/**
	 * Learn neuron network
	 *
	 * @param: EvolutionaryAlgorithm evolAlgorithm - type of algorithm using to learn neural network
	 * @param: OptymalizationType::Enum oType - independent what are you looking for: max or min
	 *
	 * @return: void
	 */

	/*
	void Learn(EvolutionaryAlgorithm * evolAlgorithm, OptymalizationType::Enum oType,
				double dInputData[]);
	*/
protected:

	/**
	 * overloaded operator []
	 *
	 * @param: unsigned int index - index of layer
	 * @return: Layer - n-Layer
	 */
	Layer & operator[](unsigned int index);

};

#endif /* NEURALNETWORK_H_ */

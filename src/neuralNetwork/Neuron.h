/*
 * Neuron.h
 *
 *  Created on: 2009-10-21
 *      Author: matik
 */

#ifndef NEURON_H_
#define NEURON_H_

//zamienic pole _iNrOfInputData na static

class Neuron
{
protected:
	//number of input data (size of neuron weights)
	int _iNrOfInputData;
	//array of weights in Neuron
	double * _aWeights;

public:

	/**
	 * constructor
	 *
	 * @param: int iNrInputData - number of input data (weights)
	 */
	Neuron( int iNrInputData );
	virtual ~Neuron();


	/**
	 * overloaded operator []
	 *
	 * @param: int - number of weight
	 * @return: double - single weight
	 */
	double & operator[](unsigned int index);


	/**
	 * set weights in neuron
	 *
	 * @param: double aWeights[] - new weights for neuron
	 */
	void setWeights( double aWeights[] ); //lub setWeights( Individual i)

	/**
	 * return neuron output
	 *
	 * @param: double aInputData[] - input signal for neuron
	 * @return: double - neuron output
	 */
	virtual double output( double aInputData[] ) = 0;

	/**
	 * return derivative of neuron output
	 *
	 * @param: double aInputData[]
	 * @return: double - derivative of neuron output
	 */
	virtual double derivativeOutput( double aInputData[] ) = 0;


	/**
	 * return nr of input data (weights)
	 *
	 * @return int
	 */
	int getNrWeights();


protected:

	/**function return neuron output
	 *
	 * @param: double inputData[] - array with input signal (data)
	 * @return: double - sum of multiplicity all weights by input signal
	 */
	double _sumator( double inputData[] );
};

#endif /* NEURON_H_ */

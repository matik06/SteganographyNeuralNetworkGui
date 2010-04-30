/*
 * Singleton.h
 *
 *  Created on: 2009-11-29
 *      Author: matik
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include "src/EnumTypes.h"


class Singleton {
public:
	~Singleton();

	//neural network
	int nrOfLayers;
	int * layersSize;
	int nrInputData;
	KindOfNeuron::Enum * neuronType;
	double * beta;
	double * alfa;
	EvolAlgorithm::Enum EvolAlgorithm;
	OptymalizationType::Enum oType;

	//soma
	double step;
	double pathLength;
	double PRT;
	double accError;
	int migrations;
	int popSizeSoma;

	//de
	double crossover;
	double mutationConstant;
	int iterations;
	int popSizeDE;

	//neural network weights
	int weightsNumber;
	double * weights;

private:
	Singleton();
	Singleton(const Singleton & singleton);

	friend Singleton & dataSettings();
};

Singleton & dataSettings();

#endif /* SINGLETON_H_ */

/*
 * EnumTypes.h
 *
 *  Created on: 2009-10-29
 *      Author: matik
 */

#ifndef ENUMTYPES_H_
#define ENUMTYPES_H_


namespace KindOfNeuron
{
    enum Enum
    {
    	SIGMOIDAL_BP_NEURON,
    	SIGMOIDAL_UP_NEURON,
    	TANH_NEURON,
    	LINEAR,
    };
}

namespace OptymalizationType
{
	enum Enum
	{
		MINIMIM,
		MAXIMUM,
	};
}

namespace EvolAlgorithm
{
	enum Enum
	{
		DE,
		SOMA,
	};
}

struct sSettings
{
	//neural network settings
	int nrOfLayers;
	int nrInputData;
	EvolAlgorithm::Enum EvolAlgorithm;
	OptymalizationType::Enum oType;

	//SOMA settings
	double step;
	double pathLength;
	double PRT;
	double accError;
	int migrations;
	int popSizeSoma;

	//DE settings
	double crossover;
	double mutationConstant;
	int iterations;
	int popSizeDE;

	//other
	int weightsNumber;
};

#endif /* ENUMTYPES_H_ */

/*
 * Algorithm.h
 *
 *  Created on: 2009-10-31
 *      Author: Mateusz Lubański
 */

#ifndef ALGORITHM_H_
#define ALGORITHM_H_

#include "Population.h"
#include "../neuralNetwork/NeuralNetwork.h"
#include "../EnumTypes.h"


class EvolutionaryAlgorithm {
protected:

	//number of individuals in population
	int _iPopSize;

	//Kind of extremum (MINIMUM, MAXIMUM)
	OptymalizationType::Enum _oType;

	//Population in Algorithm.
    Population _population;

    double * _costValueHistory;

public:

	EvolutionaryAlgorithm(int iPopSize, int iterations);
	virtual ~EvolutionaryAlgorithm() = 0;

	/**
	 * Simulation of Evolutionary Algorithm
	 *
	 * @param: OptymalizationType::Enum oType - type of optymalization (MIN or MAX)
	 * @param: NeuralNetwork network - neural network (necessary for counting cost value)
	 * @param: double dInputData[] - input data for neural network
	 *
	 * @return: Individual
	 */
	virtual Individual simulate(OptymalizationType::Enum oType, NeuralNetwork & network,
								double ** dInputData) = 0;

    /**
     * get population in algorythm
     * return Population - popularion in Algorythm
     */
	Population getPopulation();	//dlaczego nie zwrocic referencji to populacji!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

	double * getCostValueHistory();

protected:

    /**
     * get randomly number from interval (0,1)
     *
     *@return double - number from (0,1) interval
     */
    double _rand0to1();

	/**
	 * set cost value for single individual
	 *
	 * @param: Individual individual
	 * @param: NeuralNetwork network - neural network necessary for counting cv for individual
	 * @param: double dInputData[] - array with input data for neural network
	 *
	 * @return void
	 */
	void _setCV( Individual & individual, NeuralNetwork & network, double ** dInputData );

	/**
	 * set cost value for all individuals in neural network
	 *
	 * @param: Population population
	 * @param: NeuralNetwork network - neural network necessary for counting cv for individual
	 * @param: double dInputData[] - array with input data for neural network
	 *
	 * @return void
	 */
	void _setCV( Population & population, NeuralNetwork & network, double ** dInputData );

};

#endif /* ALGORITHM_H_ */

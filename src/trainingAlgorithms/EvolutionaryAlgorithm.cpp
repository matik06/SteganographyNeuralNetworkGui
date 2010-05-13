/*
 * Algorithm.cpp
 *
 *  Created on: 2009-10-31
 *      Author: frv
 */

#include "EvolutionaryAlgorithm.h"

EvolutionaryAlgorithm::EvolutionaryAlgorithm(int iPopSize, int iterations):
	_iPopSize(iPopSize), _population(iPopSize)
{
	_costValueHistory = new double[iterations];
}


EvolutionaryAlgorithm::~EvolutionaryAlgorithm() {
	// TODO Auto-generated destructor stub
}

Population EvolutionaryAlgorithm::getPopulation()
{
	return this->_population;
}


void EvolutionaryAlgorithm::_setCV( Individual & individual, NeuralNetwork & network, double ** dInputData )
{
	double  dCV = network.getCostValue( individual.getParam(), dInputData);
	individual.setCostValue( dCV );
}


void EvolutionaryAlgorithm::_setCV( Population & population, NeuralNetwork & network, double ** dInputData )
{
	int iPopulationSize = population.getPopSize();
	double dCV;

	for(int i = 0; i < iPopulationSize; i++)
	{
		dCV = network.getCostValue( population[i].getParam(), dInputData );
		population[i].setCostValue( dCV );
	}
}

double EvolutionaryAlgorithm::_rand0to1()
{
	return (0 + ((double)rand() / ((double)(RAND_MAX)+1) * (1-0)));
}

double * EvolutionaryAlgorithm::getCostValueHistory()
{
	return _costValueHistory;
}

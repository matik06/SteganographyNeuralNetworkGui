/*
 * DifferentialEvolution.h
 *
 *      Author: frv
 */

#ifndef DIFFERENTIALEVOLUTION_H_
#define DIFFERENTIALEVOLUTION_H_

#include "EvolutionaryAlgorithm.h"
#include "Population.h"


class DifferentialEvolution: public EvolutionaryAlgorithm
{
private:

	//
	double _dMutationConstant;

	//probability of crossover
	double _dCrossover;

	//Number of iterations
	int _iIterNum;


public:
	/**
	 * constructor
	 *
	 * @param double dMutationConstant - mutation constant
	 * @param double dCrossover - probability of crossover
	 * @param int iPopSize - size of population
	 */
	DifferentialEvolution(double dMutationtConstant, double dCrossover,int iPopSize,int iIterNum);


	/**
	 *copy constructor
	 *
	 * @param  DifferentialEvolution & other - constant reference to other  DifferentialEvolution object
	 */
    DifferentialEvolution(const DifferentialEvolution & other);

	/**
	 * destructor
	 */
	~DifferentialEvolution();

    /**
     *assignment operator for DifferentialEvolution
     *
     *@param DifferentialEvolution& other - other DifferentialEvolution object which values
     *                                      are assign to current DifferentialEvolution object
     *@return DifferentialEvolution& -current DifferentialEvolution object.
     */
	DifferentialEvolution& operator=(const DifferentialEvolution & other);

	/**
	 * Simulation Differential Evolution Algorithm
	 *
	 * @param OptymalizationType::Enum oType - Type of optymalization (MINIMUM,MAXIMUM)
	 * @return Individual- the best Individual after Differential Evolution Algorithm
	 */
	Individual simulate(OptymalizationType::Enum oType, NeuralNetwork & network,
						double ** dInputData);

	/**
	 * Simulation loop for one Active Individual
	 *
	 * @int iActiveIndividualIndex - index of active individual
	 */
	void _activeIndividualLoop(int iActiveIndividualIndex, NeuralNetwork & network, double ** dInputData);

private:
	/**
	 * crossover activeIndividual parameters and noisyVector parameters;
	 *
	 * @param Individual activeIndividual -active individual in current iteration
	 * @param Individual noisyVector - new individual created from 3 randomely individuals
	 * @return Individual - new individual created from crossover ActiveIndividual and NoisyVector
	 */
    Individual _crossover(Individual activeIndividual, Individual noisyVector);

    /**
     * function to choose three randomly individuals
     *
     * @param int iActiveIndividualIndex - index of active individual
     * @return Population - three randomly individuals.
     */
    Population _getThreeRandIndividuals(int iActiveIndividualIndex);

    /**
     * function to mixing individual's indexes in population using to choose three randomly individuals
     *
     * @param: int source[] - population to mixing
     */
  //  void _mixIndex(Population & source);
    void _mixIndex(int source[]);
};

#endif /* DIFFERENTIALEVOLUTION_H_ */

/*
 * SOMA.h
 *
 *  Created on: 2009-10-31
 *      Author: frv
 */

#ifndef SOMA_H_
#define SOMA_H_

#include "EvolutionaryAlgorithm.h"
#include "Population.h"

class SOMA: public  EvolutionaryAlgorithm
{
private:

	//Size of step
	double _dStep;

	//Length of path in migration loop.
	double _dPathLength;

	//using to produce PRTVector
	double _dPRT;

	//Accepted Error
	double _dAccError;

	//Number of migration loops.
	int _iMigration;


public:
	/**
	 * constructor
	 *
	 * @param double dStep - size of step
	 * @param double dPathLength - Length of path in migration loop.
	 * @param double dAccError -Accepted Error
	 * @param int iMigration - number of migrations
	 * @param int iPopSize - number of Individuals in population
	 */
	SOMA(double dStep,double dPathLength, double dPRT, double dAccError,
		 int iMigration,int iPopSize );

	/**
	 *copy constructor
	 *
	 * @param SOMA & other - constant reference to other SOMA object
	 */
    SOMA(const SOMA & other);

	/**
	 * destructor
	 */
	~SOMA();


    /**
     *assignment operator for SOMA
     *
     *@param SOMA& other - other SOMA object which values are assign to current SOMA object
     *@return SOMA& -current SOMA object .
     */
    SOMA& operator=(const SOMA & other);

	/**
	 * Simulation SOMA Algorithm
	 *
	 * @param OptymalizationType::Enum oType - Type of optymalization (MINIMUM,MAXIMUM)
	 * @return Individual- the best Individual after SOMA Algorithm
	 */
	Individual simulate(OptymalizationType::Enum oType, NeuralNetwork & network,
						double ** dInputData );

private:
	/**
	 * Generate prtVector
	 *
	 * @return int* -PRT array (PRTVector)
	 */
	int* _getPRTVector();

	/**
	 * Simulate one migration loop
	 */
	void _MigrationLoop( NeuralNetwork & network, double ** dInputData );

	/**
	 * Simulation for one individual
	 *
	 * @param int iActiveIndex - index of active individual
	 * @param int iLeaderIndex - index of the best individual
	 */
	void _ActivIndividualLoop(int iActiveIndex, int iLeaderIndex, NeuralNetwork & network,
							  double ** dInputData );

	/**
	 * Simulation for each step T for one individual
	 *
	 * @param double dt - size of jump
	 * @param int iActiveIndex - index of active individual
	 * @param int iLeaderIndex - index of leader individual
	 * return Individual - individual in dt step size
	 */
	Individual _CalculateForStep(double dt,int iActiveIndex, int iLeaderIndex);

};

#endif /* SOMA_H_ */

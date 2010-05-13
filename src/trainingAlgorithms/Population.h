/*
 * Population.h
 *
 *  Created on: 2009-10-28
 *      Author: frv
 */

#ifndef POPULATION_H_
#define POPULATION_H_

#include "Individual.h"
#include "../EnumTypes.h"

class Population {
private:
	//size of population
	int _iPopSize;

	//array of individuals
	Individual* _Individuals;
public:
	/**
	 * constructor
	 *
	 *@param int iPopSize - Size of population ( number of individuals)
	 */
	Population(int iPopSize);

	/**
	 * copy constructor
	 *
	 *@param const Population & other- constant reference to other population
	 */
	Population(const Population & other);

	/**
	 * destructor
	 */
    ~Population();

    /**
     *array operator for individual's array
     *
     *@param int iIndex - index in array of individuals
     *@return Individual - Chosen individual;
    */
    Individual&  operator[](int iIndex);

    /**
     *assignment operator for population
     *
     *@param Population& other - other population which values are assign to current population
     *@return Population& -current population .
     */
    Population& operator=(const Population & other);

    /**
     * choose the best individual in population.
     *
     *@return Individual - The best individual;
    */
    Individual getBestIndividual(OptymalizationType::Enum oType);

    /**
     * choose the best individual in population.
     *
     *@return int - The best individual's index;
    */
    int getBestIndividualIndex(OptymalizationType::Enum oType);

    /**
     * choose the worst individual in population.
     *
     *@return Individual - The worst individual;
    */
    Individual getWorstIndividual(OptymalizationType::Enum oType);

    /**
     * choose the worst individual in population.
     *
     *@return int - The worst individual's index;
    */
    int getWorstIndividualIndex(OptymalizationType::Enum oType);


    /**
     * get population size
     *
     *@return int - population size
     */
    int getPopSize();

    //print population
    void popPrint();

private:

	 /**
	  * choose individual in population which have minimum CostValue.
	  *
	  *@return int  - Minimum individual index;
	 */
	int _findMinIndividual();
	 /**
	  * choose individual in population which have maximum CostValue.
	  *
	  *@return int  - Maximum individual index;
	 */
	int _findMaxIndividual();

};


#endif /* POPULATION_H_ */



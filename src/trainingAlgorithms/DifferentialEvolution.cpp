/*
 * DifferentialEvolution.cpp
 *
 *      Author: frv
 */

#include "DifferentialEvolution.h"


DifferentialEvolution::DifferentialEvolution(double dMutationtConstant, double dCrossover,
											 int iPopSize,int iIterNum):
	EvolutionaryAlgorithm(iPopSize, iIterNum)
{
	this->_dMutationConstant = dMutationtConstant;
	this->_dCrossover = dCrossover;
	this->_iIterNum = iIterNum;
}

DifferentialEvolution::DifferentialEvolution(const DifferentialEvolution & other):
EvolutionaryAlgorithm(other._iPopSize, other._iIterNum)
{
	this->_dMutationConstant = other._dMutationConstant;
	this->_dCrossover = other._dCrossover;
	this->_iIterNum = other._iIterNum;
}

DifferentialEvolution::~DifferentialEvolution()
{
}

DifferentialEvolution & DifferentialEvolution::operator =(const DifferentialEvolution & other )
{
	this->_dMutationConstant = other._dMutationConstant;
	this->_dCrossover = other._dCrossover;
	this->_iPopSize = other._iPopSize;
	this->_iIterNum = other._iIterNum;
	this->_population=other._population;
	return *this;
}

Individual DifferentialEvolution::simulate(OptymalizationType::Enum oType, NeuralNetwork & network,
										   double ** dInputData)
{
	this->_oType = oType;

	for(int i =0; i<this->_iIterNum;i++)
	{
		for(int j=0 ; j<this->_iPopSize;j++)
		{
			_activeIndividualLoop(j, network, dInputData);
		}
		_costValueHistory[i] = _population.getBestIndividual(_oType).getCostValue();
	}
	return this->_population.getBestIndividual(this->_oType);
}

Individual DifferentialEvolution::_crossover(Individual activeIndividual,Individual noisyVector)
{
	double* tmpParam = new double [Individual::getDimensions()];
	Individual tmpInd;

	for(int i =0; i<Individual::getDimensions();i++)
	{
		if(_rand0to1()<this->_dCrossover)
		{
			tmpParam[i] = noisyVector.getParam()[i];
		}
		else
		{
			tmpParam[i]= activeIndividual.getParam()[i];
		}
	}
	tmpInd.setParam(tmpParam);
	delete[]tmpParam;
	return tmpInd;
}

Population DifferentialEvolution::_getThreeRandIndividuals(int iActiveIndividualIndex)
{
	int* tmp =new int[this->_iPopSize];

	for(int i=0 ; i<_iPopSize;i++)
	{
		tmp[i]=i;
	}
	_mixIndex(tmp);
	Population p1(3);

	int stop=0;
	int i =0;
	do
	{
		if(tmp[i]!=iActiveIndividualIndex)
		{
			p1[stop] =this->_population[tmp[i]];
			++stop;
		}
		++i;
	}
    while(stop < 3);
    delete [] tmp;
	return p1;
}

void DifferentialEvolution::_activeIndividualLoop(int iActiveIndividualIndex,
												  NeuralNetwork & network, double ** dInputData)
{
	Population threeRandIndividuals = _getThreeRandIndividuals(iActiveIndividualIndex);
	Individual tmpInd;

	tmpInd = threeRandIndividuals[0]-threeRandIndividuals[1];
	tmpInd *= this->_dMutationConstant;
	tmpInd = tmpInd + threeRandIndividuals[2];

	Individual activeInd = this->_population[iActiveIndividualIndex];
    Individual tmpNewInd = _crossover(activeInd,tmpInd);

    //set cost value for activeInd individual
    this->_setCV( activeInd, network, dInputData );
    //set cost value for tmpNewId individual
    this->_setCV( tmpNewInd, network, dInputData );

	if((_oType == OptymalizationType::MAXIMUM && activeInd<tmpNewInd)||
	  (_oType == OptymalizationType::MINIMIM && activeInd>tmpNewInd ))
	{
		this->_population[iActiveIndividualIndex] = tmpNewInd;
	}
}



void DifferentialEvolution::_mixIndex(int source[])
{
	for(int i=0; i<this->_iPopSize;i++)
	{
		int tmp = source[i];
		int tmpIndex = rand()%this->_iPopSize;
		source[i]= source[tmpIndex];
		source[tmpIndex]= tmp;
	}
}


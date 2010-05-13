/*
 * SOMA.cpp
 *
 *      Author: frv
 */

#include "SOMA.h"

SOMA::SOMA(double dStep,double dPathLength, double dPRT, double dAccError,
		   int iMigration,int iPopSize ):
	EvolutionaryAlgorithm(iPopSize, iMigration)
{
	this->_dStep =dStep;
	this->_dPathLength = dPathLength;
	this->_dAccError =dAccError;
	this->_iMigration = iMigration;
	this->_dPRT = dPRT;
}

SOMA::SOMA(const SOMA& other):
	EvolutionaryAlgorithm(other._iPopSize, other._iMigration)
{
	this->_dStep =other._dStep;
	this->_dPathLength =other._dPathLength;
	this->_dAccError =other._dAccError;
	this->_iMigration = other._iMigration;
	this->_dPRT = other._dPRT;
}

SOMA::~SOMA()
{

}

SOMA& SOMA::operator =(const SOMA & other)
{
	this->_dStep =other._dStep;
	this->_dPathLength =other._dPathLength;
	this->_dAccError =other._dAccError;
	this->_iMigration = other._iMigration;
	this->_dPRT = other._dPRT;
	this->_iPopSize = other._iPopSize;
	this->_population = other._population;
	return *this;
}
int* SOMA::_getPRTVector()
{
	int iTmp = Individual::getDimensions();
	int* _tmp = new int[iTmp];

	for(int i=0; i<iTmp;i++)
	{
		if( this->_rand0to1() < _dPRT )
		{
			_tmp[i]=1;
		}
		else
		{
			_tmp[i]=0;
		}
	}
	return _tmp;
}

Individual SOMA::simulate( OptymalizationType::Enum oType, NeuralNetwork & network,
						   double ** dInputData )
{
	double dBestCV;
	double dWorstCV;
	double dDiff;

	this->_oType = oType;
	//set cost values for all individuals in population
	this->_setCV( this->_population, network, dInputData );

	for(int i=0; i < _iMigration ; i++)
	{
		dBestCV = this->_population.getBestIndividual(this->_oType).getCostValue();
		dWorstCV = this->_population.getWorstIndividual(this->_oType).getCostValue();
		dDiff = fabs(dBestCV - dWorstCV);

		if(dDiff > _dAccError)
		{
			_MigrationLoop(network, dInputData);
			_costValueHistory[i] = _population.getBestIndividual(_oType).getCostValue();
		}
		else
		{
			break;
		}
	}
	return this->_population.getBestIndividual(_oType);
}

void SOMA::_MigrationLoop( NeuralNetwork & network, double ** dInputData )
{
	int iLeaderIndex= this->_population.getBestIndividualIndex(_oType);

	for(int i =0; i<_iPopSize;i++)
	{
		if(i != iLeaderIndex)
		{
			_ActivIndividualLoop( i, iLeaderIndex, network, dInputData );
		}
	}
}

void SOMA::_ActivIndividualLoop(int iActiveIndex, int iLeaderIndex, NeuralNetwork & network,
								double ** dInputData )
{
	int iNumStep =(int)((_dPathLength /_dStep)+1);
	Population tmpPop(iNumStep);

	for(int i=0; i<iNumStep;i++)
	{
		double dT = (i)*_dStep;
		tmpPop[i] =_CalculateForStep(dT,iActiveIndex,iLeaderIndex);

		//set cost value for individual: tmpPop[i]
		this->_setCV( tmpPop[i], network, dInputData );
	}
	Individual in = tmpPop.getBestIndividual(_oType);

	if( (_oType == OptymalizationType::MAXIMUM && (this->_population)[iActiveIndex] < in )
		||
		(_oType == OptymalizationType::MINIMIM && (this->_population)[iActiveIndex]> in ) )
	{
		this->_population[iActiveIndex] = in;
	}
}


Individual SOMA::_CalculateForStep(double dt,int iActiveIndex, int iLeaderIndex)
{
	int* PRTVector = _getPRTVector();
	int iParamNum = Individual::getDimensions();
	Individual tmpIndividual;

	double* dActiveParams = this->_population[iActiveIndex].getParam(); //Parameters of active individual
	double* dLeaderParams = this->_population[iLeaderIndex].getParam(); //Parameters of leader individual
	double* dTmpParam = new double[iParamNum];

	for(int i=0; i<iParamNum;i++)
	{
		if(PRTVector[i]==1)
		{
			dTmpParam[i] = dActiveParams[i] + (( dLeaderParams[i] - dActiveParams[i] )*dt);
		}
		else
		{
			dTmpParam[i] = dActiveParams[i];
		}
	}

	tmpIndividual.setParam(dTmpParam);

	delete [] PRTVector;
	delete [] dTmpParam;
	return tmpIndividual;	//wywoluje sie konstrukotr kopiujacy
}


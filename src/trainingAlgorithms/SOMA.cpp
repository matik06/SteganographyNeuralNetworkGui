/*
 * SOMA.cpp
 *
 *      Author: frv
 */

#include "SOMA.h"

SOMA * SOMA::getInstance( const Singleton & settings )
{
       return new SOMA(settings.step,
                       settings.pathLength,
                       settings.PRT,
                       settings.accError,
                       settings.migrations,
                       settings.popSizeSoma);
}


SOMA::SOMA(double dStep,double dPathLength, double dPRT, double dAccError,
		   int iMigration,int iPopSize ):
	EvolutionaryAlgorithm(iPopSize, iMigration)
{
	this->_dStep = dStep;
	this->_dPathLength = dPathLength;
	this->_dAccError =dAccError;
	this->_iMigration = iMigration;
	this->_dPRT = dPRT;
	this->_PRTVector = NULL;
}

SOMA::SOMA(const SOMA & other):
	EvolutionaryAlgorithm(other._iPopSize, other._iMigration)
{
	this->_dStep = other._dStep;
	this->_dPathLength = other._dPathLength;
	this->_dAccError = other._dAccError;
	this->_iMigration = other._iMigration;
	this->_dPRT = other._dPRT;
	_population = other._population;
	this->_PRTVector = NULL;
}

SOMA::~SOMA()
{

}

SOMA& SOMA::operator=(const SOMA & other)
{
	this->_dStep = other._dStep;
	this->_dPathLength = other._dPathLength;
	this->_dAccError = other._dAccError;
	this->_iMigration = other._iMigration;
	this->_dPRT = other._dPRT;
	this->_iPopSize = other._iPopSize;
	this->_population = other._population;

	return *this;
}
int* SOMA::_getPRTVector()
{
	if ( _PRTVector != NULL )
		delete _PRTVector;

	_PRTVector = new int[Individual::getDimensions()];

	for(int i = 0; i < Individual::getDimensions(); i++)
	{
		if( this->_rand0to1() <= _dPRT )
		{
			_PRTVector[i] = 1;
		}
		else
		{
			_PRTVector[i] = 0;
		}
	}

	return _PRTVector;
}

Individual SOMA::simulate( OptymalizationType::Enum oType, NeuralNetwork & network,
						   double ** aInputData, double ** aOutputData, int iNrDataSet )
{
	int iLeaderIndex;
	this->_oType = oType;
	_setCV( _population, network, aInputData[0], aOutputData[0] );
	_resetCostValueHistory( _iMigration );

	for (int i = 0; i < _iMigration; ++i)
	{
		for (int j = 0; j < iNrDataSet; ++j)
		{
			_getPRTVector();
			//get index of leader individual
			iLeaderIndex = _population.getBestIndividualIndex( oType );
			//counting cost value history
			double d = _population[iLeaderIndex]->getCostValue();
			_costValueHistory[i] += _population[iLeaderIndex]->getCostValue();
			_MigrationLoop( network, aInputData[j], aOutputData[j], iLeaderIndex );
		}
	}


	return _population.getBestIndividual( oType );

//	double dBestCV;
//	double dWorstCV;
//	double dDiff;
//
//	this->_oType = oType;
//
//	//powinien być ustawiany cost value dla wszystkich individuali ale dla poszczególnego zestawy danych......
//	//set cost values for all individuals in population
//	this->_setCV( this->_population, network, dInputData );
//
//	for(int i=0; i < _iMigration ; i++)
//	{
//		_getPRTVector();
//
//		//kaj kurwa druga pętla dla poszczególnych zestawów danych.......................
//		dBestCV = this->_population.getBestIndividual(this->_oType).getCostValue();
//		dWorstCV = this->_population.getWorstIndividual(this->_oType).getCostValue();
//		dDiff = fabs(dBestCV - dWorstCV);
//
////		if ( _dAccError != -1)
//		if(dDiff > _dAccError)
//		{
//			_MigrationLoop(network, dInputData);
//			_costValueHistory[i] = _population.getBestIndividual(_oType).getCostValue();
//		}
//		else
//		{
//			break;
//		}
//	}
//	return this->_population.getBestIndividual(_oType);
}

void SOMA::_MigrationLoop( NeuralNetwork & network, double * aInputData,
		double * aOutputData, int iLeaderIndex )
{

	for(int i = 0; i < _iPopSize; i++)
	{
		if(i != iLeaderIndex)
		{
			//create temporary population
			int iNrStep = (int) (_dPathLength / _dStep + 1);
			Population tempPop(iNrStep, false);

			tempPop[0] = new Individual( *_population[i] );
			for (int j = 1; j < iNrStep; ++j)
			{
				double dStep = j * _dStep;
				tempPop[j] = _CalculateForStep( dStep, i, iLeaderIndex);
				_setCV( *tempPop[j], network, aInputData, aOutputData );
			}

			//select best ind from tempPop and set better ind to main population
			_setBetterIndividual( i, tempPop.getBestIndividual( _oType ) );
		}
	}

//	return _population.getBestIndividual( _oType ).getCostValue();
}

void SOMA::_ActivIndividualLoop(int iActiveIndex, int iLeaderIndex, NeuralNetwork & network,
								double * aInputData, double * aOutputData )
{
//	int iNumStep =(int)((_dPathLength /_dStep)+1);
//	Population tmpPop(iNumStep, false);
//
//	for(int i=0; i<iNumStep;i++)
//	{
//		double dT = (i)*_dStep;
//		tmpPop[i] = _CalculateForStep(dT,iActiveIndex,iLeaderIndex);
//
//		//set cost value for individual: tmpPop[i]
////		this->_setCV( *tmpPop[i], network, dInputData );
//	}
//	Individual in = tmpPop.getBestIndividual(_oType);
//
//	if( (_oType == OptymalizationType::MAXIMUM && *(this->_population)[iActiveIndex] < in )
//		||
//		(_oType == OptymalizationType::MINIMIM && *(this->_population)[iActiveIndex] > in ) )
//	{
//		*this->_population[iActiveIndex] = in;
//	}
}


Individual * SOMA::_CalculateForStep(double dt,int iActiveIndex, int iLeaderIndex)
{
//	Individual * resultIndividual = new Individual( *_population[iLeaderIndex] );
//
//	*resultIndividual -= *_population[ iActiveIndex ];
//
//	for (int i = 0; i < Individual::getDimensions(); ++i)
//	{
//		if( _PRTVector[i] == 1 )
//		{
//			(*resultIndividual)[i] *= dt;
//		}
//	}
//
//	*resultIndividual += *_population[iActiveIndex];
//
//	return resultIndividual;

	int iParamNum = Individual::getDimensions();
	Individual * tmpIndividual = new Individual();

	double* dActiveParams = this->_population[iActiveIndex]->getParam(); //Parameters of active individual
	double* dLeaderParams = this->_population[iLeaderIndex]->getParam(); //Parameters of leader individual
	double* dTmpParam = new double[iParamNum];

	for(int i=0; i<iParamNum;i++)
	{
		if(_PRTVector[i]==1)
		{
			dTmpParam[i] = dActiveParams[i] + (( dLeaderParams[i] - dActiveParams[i] )*dt);
		}
		else
		{
			dTmpParam[i] = dActiveParams[i];
		}
	}

	tmpIndividual->setParam(dTmpParam);

	delete [] dTmpParam;
	return tmpIndividual;
}


void SOMA::_setBetterIndividual( int iActiveInd, Individual & newInd )
{
	if ( _oType == OptymalizationType::MINIMIM )
	{
		if ( *_population[iActiveInd] > newInd )
		{
			*_population[iActiveInd] = newInd;
		}
	}
	else if ( _oType == OptymalizationType::MAXIMUM )
	{
		if ( *_population[iActiveInd] < newInd )
		{
			*_population[iActiveInd] = newInd;
		}
	}
}

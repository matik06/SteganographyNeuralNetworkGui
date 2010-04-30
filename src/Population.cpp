/*
 * Population.cpp
 *
 *      Author: frv
 */

#include "Population.h"


Population::Population(int iPopSize)
{
	this->_iPopSize = iPopSize;
	this->_Individuals = new Individual[iPopSize];
}

Population::Population(const Population & other)
{
	this->_iPopSize = other._iPopSize;
	this->_Individuals = new Individual[this->_iPopSize];
	for(int i = 0;i<this->_iPopSize;i++)
	{
		this->_Individuals[i] = other._Individuals[i];
	}
}

Population::~Population()
{
	delete[] _Individuals;
}

Individual& Population::operator[](int iIndex)
{
	return this->_Individuals[iIndex];
}

Population& Population::operator =(const Population & other)
{
	delete[] this->_Individuals;
	this->_Individuals = new Individual[_iPopSize];

	for(int i =0; i<_iPopSize; i++)
	{
		this->_Individuals[i] = other._Individuals[i];
	}
	return *this;
}

Individual Population::getBestIndividual(OptymalizationType::Enum oType)
{
      int iIndex = getBestIndividualIndex(oType);
      return this-> _Individuals[iIndex];
}

Individual Population::getWorstIndividual(OptymalizationType::Enum oType)
{
      int iIndex = getWorstIndividualIndex(oType);
      return this-> _Individuals[iIndex];
}

int Population::getBestIndividualIndex(OptymalizationType::Enum oType)
{
	switch(oType)
	{
		case OptymalizationType::MINIMIM: return _findMinIndividual();
		 break;

		case OptymalizationType::MAXIMUM: return _findMaxIndividual();
		 break;
	}
	return -1;
}
int Population::getWorstIndividualIndex(OptymalizationType::Enum oType)
{
	switch(oType)
		{
			case OptymalizationType::MAXIMUM: return _findMinIndividual();
			 break;

			case OptymalizationType::MINIMIM: return _findMaxIndividual();
			 break;
		}
		return -1;
}

int Population::getPopSize()
{
	return _iPopSize;
}

void Population::popPrint()
{
	int iDimension= Individual::getDimensions();
	for(int i=0 ;i< _iPopSize;i++)
	{
			std::cout<< "Os."<<i+1<<" : ";

			for (int j =0; j<iDimension-1; j++)
			{
				std::cout<<this->_Individuals[i].getParam()[j]<<" , ";
			}
			std::cout<<this-> _Individuals[i].getParam()[iDimension-1]<< " = ";
			std::cout<<this->_Individuals[i].getCostValue()<<std::endl;
		}
	std::cout<< "best is = Os."<<(getBestIndividualIndex(OptymalizationType::MINIMIM)+1)<<std::endl;
}


int Population::_findMinIndividual()
{
	int iBestIndex=0;
	Individual BestIndividual = this-> _Individuals[0];

	for(int i=1 ; i<_iPopSize ; i++)
	{
		if(BestIndividual>this-> _Individuals[i])
		{
			BestIndividual =this-> _Individuals[i];
			iBestIndex = i;
		}
		else{}
	}
	return iBestIndex;
}

int Population::_findMaxIndividual()
{
	int iBestIndex=0;
	Individual BestIndividual = this-> _Individuals[0];

	for(int i=1 ; i<this->_iPopSize ; i++)
	{
		if(BestIndividual < this-> _Individuals[i])
		{
			BestIndividual =this-> _Individuals[i];
			iBestIndex = i;
		}
	}
	return iBestIndex;
}


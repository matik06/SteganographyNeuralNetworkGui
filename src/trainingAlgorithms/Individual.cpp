/*
 * Individual.cpp
 *
 *  Created on: 2009-10-28
 *      Author: frv
 */

#include "Individual.h"


int Individual::_iDimensions =0;
double Individual::_dBegin = 0;
double Individual::_dEnd = 0;

Individual::Individual() {

	_aParam = new double[_iDimensions];

	for(int i=0; i<_iDimensions; i++)
	{
		_aParam[i]= _randWeight();
	}

    this->_dCostValue = 0;
}

Individual::Individual(const Individual & other)
{
	this->_aParam = new double [this->_iDimensions];

	for(int i =0; i < this->_iDimensions; i++)
	{
		this->_aParam[i] = other._aParam[i];
	}
	this->_dCostValue =other._dCostValue;
}

Individual::~Individual()
{
	delete [] _aParam;
}

int Individual::getDimensions()
{
	return _iDimensions;
}

void Individual::setDimensions(int iDimensions)
{
	_iDimensions = iDimensions;
}

void Individual::setBegin(double dBegin)
{
	_dBegin = dBegin;
}

void Individual::setEnd(double dEnd)
{
	_dEnd = dEnd;
}

void Individual::setParam(double aParam[])
{
	for(int i=0; i<_iDimensions; i++)
	{
		this->_aParam[i] = aParam[i];
	}
}

double* Individual::getParam()
{
	return this->_aParam;
}

Individual  Individual::operator +(const Individual & other)
{
	Individual tmp ;

	for(int i=0; i<_iDimensions; i++)
	{
		tmp._aParam[i] =this->_aParam[i]+ other._aParam[i];
	}
	return tmp;
}


Individual  Individual::operator -(const Individual & other)
{
	Individual tmp;

	for(int i=0; i<_iDimensions; i++)
	{
		tmp._aParam[i]=this->_aParam[i]-= other._aParam[i];
	}
	return tmp;
}


Individual Individual::operator *=(double dValue)
{
	for(int i=0; i<_iDimensions; i++)
	{
		this->_aParam[i]*= dValue;
	}
	return *this;
}

int Individual::operator >(const Individual& other)
{
	if(this->_dCostValue > other._dCostValue)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Individual::operator <(const Individual& other)
{
	if(this->_dCostValue < other._dCostValue)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


double Individual::getCostValue()
{
	return this->_dCostValue;
}

void Individual::setCostValue( double dValue )
{
	this->_dCostValue = dValue;
}

void Individual::indPrint()
{
	for(int i=0; i<_iDimensions-1; i++)
	{
		std::cout<< _aParam[i]<<" , ";
	}
	std::cout << _aParam[_iDimensions-1]<< "  CV = ";
	std::cout<< _dCostValue << std::endl;
}

double Individual::_randWeight()
{
	return _dBegin + ((double)rand() / ((double)(RAND_MAX)+1) * (_dEnd-_dBegin));
}


Individual& Individual::operator=(const Individual& other)
{
	for(int i=0 ; i<_iDimensions ;i++)
	{
		this->_aParam[i] = other._aParam[i];
	}
	this->_dCostValue = other._dCostValue;
    return *this;
}


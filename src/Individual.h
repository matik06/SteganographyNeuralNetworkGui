/*
 * Individual.h
 *
 *      Author: frv
 */

#ifndef INDIVIDUAL_H_
#define INDIVIDUAL_H_

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <ctime>

#include "NeuralNetwork.h"

class Individual {

private	:
	//array of individual parameters
	double*  _aParam;

	//costValue for actual parameters
    double _dCostValue;

	//number of dimensions
	static int _iDimensions;

	//begin of section which weights(parameters) can be.
	static double _dBegin;

	//end of section which weights(parameters) can be.
	static double _dEnd;


public:
	/**
	 * default constructor
	 */
	Individual();

	/**
	 * copy constructor
	 *
	 * @param const Individual & other - other object of Individual class using to create new object.
	 */
	Individual(const Individual & other);

	/**
	 * destructor
	 */
    ~Individual();

    /**
    * set parameters for individual
    *
    *@param double aParam[]  - new parameters for individual.
    */
    void setParam(double aParam[]);

    /**
    * get individual parameters
    *
    *@return double* -array of individual parameters .
    */
    double* getParam();

    /**
    * get CostValue
    *
    *@return double -individual's CostValue .
    */
    double getCostValue();

    /**
     * set cost value for individual
     *
     * @param: double value - new value for cost value in individual
     * @return: void
     */
    void setCostValue( double dValue );

    /**
    * get number of parameters
    *
    *@return int - number of parameters (dimensions) .
    */
    static int getDimensions();

    /**
     * get number of parameters
     *
     *@param int iDimensions - new dimensions number
    */
    static void setDimensions(int iDimensions);

    /**
     * get number of parameters
     *
     *@param double dBegin -  begin of section which weights can be.
    */
    static void setBegin(double dBegin);

    /**
     * get number of parameters
     *
     *@param double dEnd -  end of section which weights can be.
    */
    static void setEnd(double dEnd);


    /**
    * operator + for individual
    *
    *@param const Individual & other - other individual to add
    *@return Individual& - new individual .
    */
    Individual  operator+(const Individual & other);

    /**
    * operator - for individual
    *
    *@param const Individual & other - other individual to subtraction
    *@return Individual& -new individual .
    */
    Individual  operator-(const Individual & other);

    /**
    * operator *= for individual
    *
    *@param double value - value to multiply with all parameters of individual
    *@return Individual -new individual .
    */
    Individual operator*=(double dValue);

    /**
     * assignment operator for individual
     *
     *@param Individual& other - other individual which values are assign to current individual
     *@return Individual& -current individual .
     */
    Individual & operator=(const Individual & other);

    /**
    * operator > for individual
    *
    *@param Individual other - other individual's Costvalue to compare with current CostValue
    *@return int -return 1 if current iCostValue is higher than CostValue in other Individual
    *             otherwise return 0.
    */
    int operator>(const Individual& other);

    /**
     * operator < for individual
     *
     *@param Individual other - other individual's Costvalue to compare with current CostValue
     *@return int -return 1 if current iCostValue is lower than CostValue in other Individual
     *             otherwise return 0.
     */
     int operator<(const Individual& other);

     /**
      * print individual
      */
     void indPrint();
private:

    /**
     * genetares randomely weight
     *
     *@return double -new weight.
     */
	double _randWeight();
public:

};

#endif /* INDIVIDUAL_H_ */

/*
 * Singleton.h
 *
 *  Created on: 2009-11-29
 *      Author: matik
 */

#ifndef SINGLETON_H_
#define SINGLETON_H_

#include <cstdlib>
#include "EnumTypes.h"
#include <QString>


class Singleton {

private:
	//dopisać ścieżkę, nazwę pliku dla wag, nazwę pliku wynikowego po nauczaniu

public:

	const QString PROGRAM_SETTINGS_FILE_NAME;

	~Singleton();


	//neural network
	int nrOfLayers;
	int * layersSize;
	int nrInputData;
	KindOfNeuron::Enum * neuronType;
	double * beta;
	double * alfa;
	EvolAlgorithm::Enum EvolAlgorithm;
	OptymalizationType::Enum oType;

	//soma
	double step;
	double pathLength;
	double PRT;
	double accError;
	int migrations;
	int popSizeSoma;

	//de
	double crossover;
	double mutationConstant;
	int iterations;
	int popSizeDE;

	//neural network weights
	int weightsNumber;
//	bool isWeights;
	double * weights;

	int getNrWeights();
	void setDeafultValues();

private:
	Singleton();
	Singleton(const Singleton & singleton);

	friend Singleton & dataSettings();

	template <class T>
	void initializeArray(T *& array, int size);
};

Singleton & dataSettings();

#endif /* SINGLETON_H_ */

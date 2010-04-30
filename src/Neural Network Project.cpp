//============================================================================
// Name        : Neural.cpp
// Author      : Mateusz Lubańśki
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#include "EnumTypes.h"
#include "NeuralNetwork.h"
#include "Individual.h"
#include "EvolutionaryAlgorithm.h"
#include "SOMA.h"
#include "DifferentialEvolution.h"

using namespace std;

void print(int * tab);
void print(double * tab);

int main() {

	int tab[] = {5, 4, 3};
	double input[] = {0.1, 0.2, 0.3, 0.4};
	double alfaibeta[] = {0.1, 0.5, 0.5};
	KindOfNeuron::Enum neuronsType[] = {KindOfNeuron::SIGMOIDAL_BP_NEURON,
										KindOfNeuron::SIGMOIDAL_UP_NEURON,
										KindOfNeuron::TANH_NEURON};

	NeuralNetwork * network =  new NeuralNetwork(3, tab, 4, neuronsType, alfaibeta, alfaibeta);
	double patterns[] = {0.8, 0.7, 0.01};
	network->setPatterns(patterns);

	Individual::setBegin(0);
	Individual::setEnd(1);
	Individual::setDimensions(52);

//	EvolutionaryAlgorithm * eAlg = new DifferentialEvolution(0.8, 0.5, 5, 20);
	EvolutionaryAlgorithm * eAlg = new SOMA(0.3, 3.0, 0.4, -1, 20, 10);

	Individual ind = eAlg->simulate(OptymalizationType::MINIMIM, *network, input);
	ind.indPrint();

	double * tabb = eAlg->getCostValueHistory();

	cout << endl;
	for(int i = 0; i < 20; i++)
	{
		cout << tabb[i] << endl;
	}

	delete network;
	delete eAlg;

	return 0;
}


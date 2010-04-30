/*
 * Layer.cpp
 *
 *  Created on: 2009-10-28
 *      Author: matik
 */

#include "Layer.h"


Layer::Layer( int iNeuronNumbers, int iInputNumbers, KindOfNeuron::Enum neuronType,
			  double dAlfa,  double dBeta ):
    _iNrNeurons(iNeuronNumbers)
{
	//create array of Neuron pointers
	this->_aNeurons = new Neuron*[this->_iNrNeurons];

	//initialize neuron array
	this->_setNeurons( neuronType, iInputNumbers, dAlfa, dBeta );
}


Layer::~Layer()
{
	//deleting all neuron pointers in _aNeurons[] array
	for(int i = 0; i < this->_iNrNeurons; i++)
	{
		delete this->_aNeurons[i];
	}

	//deleting _aNeurons[] array
	delete [] this->_aNeurons;
}


Neuron & Layer::operator [](unsigned int index )
{
	return *this->_aNeurons[index];
}


void Layer::_setNeurons( KindOfNeuron::Enum neuronType, int iNrInputData,
						 double dAlfa, double dBeta )
{
	switch(neuronType)
	{
		case KindOfNeuron::SIGMOIDAL_UP_NEURON:
			for(int i = 0; i < this->_iNrNeurons; i++)
			{
				this->_aNeurons[i] = new SigmoidalUPNeuron(iNrInputData, dBeta);
			}; break;

		case KindOfNeuron::SIGMOIDAL_BP_NEURON:
			for(int i = 0; i < this->_iNrNeurons; i++)
			{
				this->_aNeurons[i] = new SigmoidalBPNeuron(iNrInputData, dBeta);
			}; break;

		case KindOfNeuron::TANH_NEURON:
			for(int i = 0; i < this->_iNrNeurons; i++)
			{
				this->_aNeurons[i] = new TanhNeuron(iNrInputData, dAlfa);
			}; break;
	}
}

double * Layer::getLayerOutput( double aInputData[] )
{
	//creating array for Neuron Network output
	double * aLayerOutput = new double[this->_iNrNeurons];

	//initialization array with output signals
	for(int i = 0; i < this->_iNrNeurons; i++)
	{
		aLayerOutput[i] = this->_aNeurons[i]->output( aInputData );
	}

	return aLayerOutput;
}

int Layer::getLayerSize()
{
	return this->_iNrNeurons;
}

int Layer::getNrInputData()
{
	// this->operator [](0) - return *this->_aNeurons[0]
	return this->operator [](0).getNrWeights();

}


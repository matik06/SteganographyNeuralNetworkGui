///*
// * RecognizeTool.cpp
// *
// *  Created on: 2009-11-14
// *      Author: matik
// */
//
//#include "RecognizeTool.h"
//
//RecognizeTool::RecognizeTool( NeuralNetwork * network, EvolutionaryAlgorithm * eAlgorithm )
//{
//	//dopisz konstruktor kopiujacy dla NeuralNetwork i zmien to!!
//	this->_network = network;
//	this->_eAlgorithm = eAlgorithm;
//
//	//set default paths to files with input and output data
//	this->_sInputData = "inputData.txt";
//	this->_sOutputData = "outputData.txt";
//}
//
//
//RecognizeTool::~RecognizeTool()
//{
//	// TODO Auto-generated destructor stub
//}
//
//void RecognizeTool::learn( OptymalizationType::Enum optymalizationType )
//{
//	double * inputData = this->_getInputData();
//	Individual individual = this->_eAlgorithm->simulate( optymalizationType, *this->_network,
//														 inputData );
//	this->_network->setWeights( individual.getParam() );
//}
//
//void RecognizeTool::simulate( OptymalizationType::Enum optymalizationType )
//{
//	double * inputData = this->_getInputData();
//	double * outputData;
//	outputData = this->_network->getNeuralNetworkOutput( inputData );
//
//	//zapisac do pliku??
//	//czy inputData ma byc int czy double??
//}
//
//
//void RecognizeTool::setInputDataFilePath( std::string inputDataFilePath )
//{
//	this->_sInputData = inputDataFilePath;
//}
//
//
//void RecognizeTool::setOutputDataFilePath( std::string outputDataFilePath )
//{
//	this->_sOutputData = outputDataFilePath;
//}
//
//
//double * RecognizeTool::_getInputData()
//{
//	/*
//		istream fin("nazwa_pliku");
//		fin >>  liczba1 >> liczba2 >> liczba3;
//		fin.close();
//	 */
//	return 0;
//}
//
//
//void RecognizeTool::_saveOutputData( double aOutputData[] )
//{
//	/*
//	ostream fout("nazwa_pliku");
//	fout << liczba1 << endl << liczba2 << endl << liczba3 << endl;
//	fout.close();
//	*/
//}

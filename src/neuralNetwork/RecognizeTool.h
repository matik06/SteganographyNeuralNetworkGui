///*
// * RecognizeTool.h
// *
// *  Created on: 2009-11-14
// *      Author: matik
// */
//
//#ifndef RECOGNIZETOOL_H_
//#define RECOGNIZETOOL_H_
//
//#include <string>
//#include <sstream>
//#include <fstream>
//
//#include "NeuralNetwork.h"
//#include "../trainingAlgorithms/SOMA.h"
//#include "../trainingAlgorithms/DifferentialEvolution.h"
//#include "../trainingAlgorithms/EvolutionaryAlgorithm.h"
//
///**
// * nie wiem jak beda zapisane dane wejsciowe, moja propozycja to:
// * w pierwszym wierszu liczba danych do wczytania
// * w drugim wierszu kolejno zapisane dane oddzielone spacja
// *
// * nie wiem czy funkcja simulate ma zwracac cos czy tylko zapisac
// * dane wyjsciowe do pliku w ktorym takie dane beda przechowywane
// *
// */
//class RecognizeTool
//{
//protected:
//
//	NeuralNetwork * _network;
//	EvolutionaryAlgorithm * _eAlgorithm;
//	std::string _sInputData;
//	std::string _sOutputData;
//
//public:
//
//	RecognizeTool( NeuralNetwork * network, EvolutionaryAlgorithm * eAlgorithm );
//	~RecognizeTool();
//
//	void learn( OptymalizationType::Enum optymalizationType );
//
//	/**
//	 * save output data in _sOutputData.txt file
//	 */
//	void simulate( OptymalizationType::Enum optymalizationType );
//
//	/**
//	 * change path for file with input data
//	 *
//	 * @param: string inputDataFilepath - path to txt file with input data
//	 * @return: void
//	 */
//	void setInputDataFilePath(std::string inputDataFilePath);
//
//	/**
//	 * change path for file with output data
//	 *
//	 * @param: string outputtDataFilepath - path to txt file with input data
//	 * @return: void
//	 */
//	void setOutputDataFilePath(std::string outputDataFilePath);
//
//protected:
//
//	/**
//	 * read input data from txt file (_sInputData.txt)
//	 *
//	 * @return: int * - array with input data
//	 */
//	double * _getInputData();
//
//
//	/**
//	 * save output data to _sOutputData.txt file
//	 *
//	 * @param: double aOutputData[] - array with output data
//	 * @return void
//	 */
//	void _saveOutputData( double aOutputData[] );
//
//};
//
//#endif /* RECOGNIZETOOL_H_ */

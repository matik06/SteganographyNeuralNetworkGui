/*
 * FileManager.h
 *
 *  Created on: 2010-05-07
 *      Author: matik
 */

#ifndef FILEMANAGER_H_
#define FILEMANAGER_H_

#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QChar>

class FileManager {

protected:

	/**
	 * file for reading or saving data
	 */
	QFile * _file;

	/**
	 * name of main folder where all files are saving
	 */
	static QString _sMainFolderName;

public:
	/**
	 * constructor for saving data in file
	 *
	 * @param: QString fileName - name of file
	 */
	FileManager(QString fileName);

	/**
	 * constructor fro reading data from file
	 *
	 * @param: QString path - path to file
	 * @param: QString fileName - name of file
	 */
	FileManager(QString path, QString fileName);

	/**
	 * descructor
	 */
	virtual ~FileManager();


	/**
	 * reading data from file to arrays
	 *
	 * @param: int iNrInput - number of input data (first part of data numbers)
	 * @param: int iNrOutput - number of output data (second part of data numbers)
	 * @param: double **& aInputs - array to save input data
	 * @param: double **& aOputut - array to save output data
	 *
	 * @return: bool - true when everyghing go fine (file have to be opened for reading,
	 * 				  in file have to be more than 2 sets of data)
	 */
	bool readData(int iNrInput, int iNrOutput, double **& aInputs, double **& aOutputs);

	/**
	 * saving weights in txt file
	 *
	 * @param: int iNrLayer - number of layer in neuron network
	 * @param: int iNrNeurons [] - number of neurons in every layer
	 * @param: int iNrWeights - number of weights in first layer
	 * @param: double *** aWeights - weights (data for writing to file)
	 */
	bool createFileWithWeights(int iNrLayer, int iNrNeurons [], int iNrWeights,
			double *** aWeights);

protected:

	/**
	 * create main file in current directory (all other files are saving in this folder)
	 *
	 * @param: QString folderName - name of folder
	 */
	static void createMainFoder(QString folderName);

	/**
	 * saving to array data with numbers
	 *
	 * @param: QTextStream & ts - data with sets (numbers)
	 * @param: double * aData - array where we save numbers
	 * @param: int iDataSize - size of array (number of data for saving)
	 */
	void readData(QTextStream & ts, double * aData, int iDataSize);

	/**
	 * removing char from data
	 *
	 * @param: QTextStream & ts - file with data
	 * @param: char c - char for reading
	 */
	void readChar(QTextStream & ts, char c);

	/**
	 * initializing array
	 *
	 * @param: double **& aData - array to initialize
	 * @param: int iNrDataSet - first dimension of array (number of data sets)
	 * @param: int iNrData - second dimension of array (number of numbers in set)
	 */
	void initializeArray(double **& aData, int iNrDataSet, int iNrData);

	/**
	 * writing ',' in file if the number is not the last one in set
	 *
	 * @param: QTextStream & ts - file with data
	 * @param: int index - current index
	 * @param: int max - number of data in set
	 */
	void writeComa(QTextStream & ts, int index, int max);

	/**
	 * counting number of data sets in file
	 *
	 * @param: QTextStream & ts - file with data	 *
	 * @return: int - number of data sets in file with data
	 */
	int countNrSets(QTextStream & ts);

};

#endif /* FILEMANAGER_H_ */

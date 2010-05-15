/*
 * ReadDataFile.h
 *
 *  Created on: 2010-05-14
 *      Author: matik
 */

#ifndef READDATAFILE_H_
#define READDATAFILE_H_

#include <QFile>
#include <QString>
#include <QTextStream>
#include <QDataStream>

#include "Singleton.h"

class ReadDataFile {

protected:
	QFile * _file;

public:
	ReadDataFile( QString path, QString fileName );
	virtual ~ReadDataFile();

	int loadFileWithInputs(int iNrInput, int iNrOutput, double **& aInputs,
			double **& aOutputs);
	void loadSettingsFromFile( Singleton & settings, bool neuralNetworkWeights );

protected:

	void readData(QTextStream & ts, double * aData, int iDataSize);
	void readChar(QTextStream & ts, char c);

	void initializeArray(double **& aData, int iNrDataSet, int iNrData);
	int countNrSets(QTextStream & ts);

	template <class T>
	void initializeArray(T *& aData, int size);

	template <class T>
	void loadArray( QDataStream & ds, T *& aData, int size);

	template <class T>
	void loadEnumArray( QDataStream & ds, T *& array, int size);
};


#endif /* READDATAFILE_H_ */
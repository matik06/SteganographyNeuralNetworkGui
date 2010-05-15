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
	 * file for reading of gor saving data
	 */
	QFile * _file;
	static QString _sMainFolderName;

public:
	FileManager(QString fileName);
	FileManager(QString path, QString fileName);
	FileManager();

	virtual ~FileManager();



	bool readData(int iNrInput, int iNrOutput, double **& aInputs, double **& aOutputs);

	bool createFileWithWeights(int iNrLayer, int iNrNeurons [], int iNrWeights,
			double *** aWeights);

	static void createMainFoder();

protected:



	void readData(QTextStream & ts, double * aData, int iDataSize);
	void readChar(QTextStream & ts, char c);
	void initializeArray(double **& aData, int iNrDataSet, int iNrData);

	void writeComa(QTextStream & ts, int index, int max);

	int countNrSets(QTextStream & ts);

};

#endif /* FILEMANAGER_H_ */

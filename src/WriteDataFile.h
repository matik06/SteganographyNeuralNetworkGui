/*
 * WriteDataFile.h
 *
 *  Created on: 2010-05-14
 *      Author: matik
 */

#ifndef WRITEDATAFILE_H_
#define WRITEDATAFILE_H_

#include "Singleton.h"

#include <QFile>
#include <QDir>
#include <QString>
#include <QTextStream>


class WriteDataFile {

public:

	static const QString MAIN_FOLDER_NAME;

protected:

	QFile * _file;
	const int _WEIGHT_PRECISION;

public:

	WriteDataFile( QString fileName );
	virtual ~WriteDataFile();

	static void createMainFoder(QString folderName);
	static void createMainFolder();

	bool saveWeightsToTxtFile(int iNrLayer, int iNrNeurons [], int iNrWeights,
			double *** aWeights);

	void saveSettingsToFile( Singleton & settings, bool neuralNetworkWeights );

	void saveRecognitionStatistics( double ** aData, int iNrData, int correct,
			int incorrect);

protected:

	void writeComa(QTextStream & ts, int index, int max);

	template <class T>
	void saveArray( QDataStream & ts, T * array, int size );


};

#endif /* WRITEDATAFILE_H_ */

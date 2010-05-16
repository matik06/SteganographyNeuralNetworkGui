#ifndef MAINWINDOW_H
#define MAINWINDOW_H

class QPushButton;

#include <QtGui/QWidget>
#include "ui_mainwindow.h"
#include "networksettings.h"
#include "src/EnumTypes.h"
#include "src/neuralNetwork/NeuralNetwork.h"
#include "src/trainingAlgorithms/EvolutionaryAlgorithm.h"
#include "src/trainingAlgorithms/SOMA.h"
#include "src/trainingAlgorithms/DifferentialEvolution.h"
#include "learningstacistics.h"
#include "src/trainingAlgorithms/Individual.h"

#include "src/FileManager.h"
#include "src/ReadDataFile.h"
#include "src/WriteDataFile.h"
#include <sstream>
#include <string>


class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool getInputsFromFile(QString fileName,double** inputsDouble, QString *inputs);
public slots:
	void settings();
	void about();
	void learning();
	void recognize();
	void saveToFile();
    void importSettings();
    void exportSettings();

private:
    Ui::MainWindowClass ui;
    void saveSettingsToFile(QString fileName, bool weights);
    void readSettingsFromFile();

    QVBoxLayout * createButtonsLayout();

    QPushButton * learnNetworkButton;
    QPushButton * readInputDataButton;
    QPushButton * recognizeButton;
    QPushButton * settingsButton;
    QPushButton * aboutButton;
    QPushButton * saveToFileButton;
    QPushButton * expotrSettingsToFileButton;
    QPushButton * importSettingsFromFileButton;
    QPushButton * exitButton;

    NetworkSettings * networkSettings;
    LearningStacistics * stat;

    QString * _inputs;
    int _numOfInputData;
    double** _inputsDouble;
    double**_outputs;
    QString _patternFileName;
    bool inputData;
    bool learned;

    //neural network objects
    NeuralNetwork * neuralNetwork;
    EvolutionaryAlgorithm * evolutionaryAlgorithm;
    void learn(double * inputs, double * patterns);

    bool _checkInputFile(QString firstLine); //!!!!!!!!!!!!!!
    bool _checkPatternsFile(QString firstLine);//!!!!!!!!!!!!!
    void _saveNeuralNetworkSettings(QString filename);
    void _saveResultsToFile(QString filename);//!!!!!!!!!!!!!!!!!!!!!!!!!
    bool _getPatternsFromFile(QString fileName, double** inputs, double** outputs);
    int _getNumberOfLines(QString& fileName);//!!!!!!!!!!!!!!!!!
    QString _getWeights();
    QString _getSOMADetails();
    QString _getDEDetails();
    QString _getKindOfNeuron(int index);
    QString _getOptimalizationType();
    void initializeNeuralNetworkObjects();
    QString doubletostring(double tab[], int size);
    QString doubletostring(int tab[], int size);
    int _getWeightsNr();
};

#endif // MAINWINDOW_H

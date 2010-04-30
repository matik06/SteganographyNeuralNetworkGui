#include "neuralnetworkgui.h"

#include <QtGui>
#include <QApplication>

#include "mainwindow.h"
#include "src/EvolutionaryAlgorithm.h"
#include "src/NeuralNetwork.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow * mainWindow = new MainWindow();
    mainWindow->show();

    return a.exec();
}

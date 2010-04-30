#ifndef NEURALNETWORKGUI_H
#define NEURALNETWORKGUI_H

#include <QtGui/QWidget>
#include "ui_neuralnetworkgui.h"

class NeuralNetworkGui : public QWidget
{
    Q_OBJECT

public:
    NeuralNetworkGui(QWidget *parent = 0);
    ~NeuralNetworkGui();

private:
    Ui::NeuralNetworkGuiClass ui;
};

#endif // NEURALNETWORKGUI_H

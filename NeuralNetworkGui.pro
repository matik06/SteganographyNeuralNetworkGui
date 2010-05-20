TEMPLATE = app
TARGET = NeuralNetworkGui
QT += core \
    gui
HEADERS += src/ReadDataFile.h \
    src/Singleton.h \
    src/WriteDataFile.h \
    src/neuralNetwork/Layer.h \
    src/neuralNetwork/LinearNeuron.h \
    src/neuralNetwork/NeuralNetwork.h \
    src/neuralNetwork/Neuron.h \
    src/neuralNetwork/RecognizeTool.h \
    src/neuralNetwork/SigmoidalBPNeuron.h \
    src/neuralNetwork/SigmoidalNeuron.h \
    src/neuralNetwork/SigmoidalUPNeuron.h \
    src/neuralNetwork/TanhNeuron.h \
    src/trainingAlgorithms/DifferentialEvolution.h \
    src/trainingAlgorithms/EvolutionaryAlgorithm.h \
    src/trainingAlgorithms/Individual.h \
    src/trainingAlgorithms/Population.h \
    src/trainingAlgorithms/SOMA.h \
    learningstacistics.h \
    src/EnumTypes.h \
    de.h \
    layerssize.h \
    mainwindow.h \
    networksettings.h \
    soma.h \
    neuralnetworkgui.h
SOURCES += src/ReadDataFile.cpp \
    src/Singleton.cpp \
    src/WriteDataFile.cpp \
    src/neuralNetwork/Layer.cpp \
    src/neuralNetwork/LinearNeuron.cpp \
    src/neuralNetwork/NeuralNetwork.cpp \
    src/neuralNetwork/Neuron.cpp \
    src/neuralNetwork/RecognizeTool.cpp \
    src/neuralNetwork/SigmoidalBPNeuron.cpp \
    src/neuralNetwork/SigmoidalNeuron.cpp \
    src/neuralNetwork/SigmoidalUPNeuron.cpp \
    src/neuralNetwork/TanhNeuron.cpp \
    src/trainingAlgorithms/DifferentialEvolution.cpp \
    src/trainingAlgorithms/EvolutionaryAlgorithm.cpp \
    src/trainingAlgorithms/Individual.cpp \
    src/trainingAlgorithms/Population.cpp \
    src/trainingAlgorithms/SOMA.cpp \
    learningstacistics.cpp \
    de.cpp \
    layerssize.cpp \
    mainwindow.cpp \
    networksettings.cpp \
    soma.cpp \
    main.cpp \
    neuralnetworkgui.cpp
FORMS += de.ui \
    layerssize.ui \
    mainwindow.ui \
    networksettings.ui \
    soma.ui \
    neuralnetworkgui.ui
RESOURCES += 

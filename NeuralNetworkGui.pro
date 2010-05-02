TEMPLATE = app
TARGET = NeuralNetworkGui
QT += core \
    gui
HEADERS += learningstacistics.h \
    src/DifferentialEvolution.h \
    src/EnumTypes.h \
    src/EvolutionaryAlgorithm.h \
    src/Individual.h \
    src/Layer.h \
    src/NeuralNetwork.h \
    src/Neuron.h \
    src/Population.h \
    src/SOMA.h \
    src/SigmoidalBPNeuron.h \
    src/SigmoidalNeuron.h \
    src/SigmoidalUPNeuron.h \
    src/TanhNeuron.h \
    Singleton.h \
    de.h \
    layerssize.h \
    mainwindow.h \
    networksettings.h \
    soma.h \
    neuralnetworkgui.h
SOURCES += learningstacistics.cpp \
    src/DifferentialEvolution.cpp \
    src/EvolutionaryAlgorithm.cpp \
    src/Individual.cpp \
    src/Layer.cpp \
    src/NeuralNetwork.cpp \
    src/Neuron.cpp \
    src/Population.cpp \
    src/SOMA.cpp \
    src/SigmoidalBPNeuron.cpp \
    src/SigmoidalNeuron.cpp \
    src/SigmoidalUPNeuron.cpp \
    src/TanhNeuron.cpp \
    Singleton.cpp \
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

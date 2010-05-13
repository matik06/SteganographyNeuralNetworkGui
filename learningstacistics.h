#ifndef LEARNINGSTACISTICS_H
#define LEARNINGSTACISTICS_H

#include <QtGui/QWidget>
#include "src/Singleton.h"
#include "src/EnumTypes.h"

class QTextEdit;
class QPushButton;

class LearningStacistics : public QWidget
{
    Q_OBJECT

public:
    LearningStacistics(QWidget *parent = 0);
    ~LearningStacistics();
    void showRessults(double* results);
    void showQstring(QString source);
public slots:
	void hideResults();
	void saveToFile();

private:
    QTextEdit* learningResults;
    QPushButton* ok;
    QPushButton* save;

};

#endif // LEARNINGSTACISTICS_H

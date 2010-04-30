#include "learningstacistics.h"
#include <QtGui>

LearningStacistics::LearningStacistics(QWidget *parent)
    : QWidget(parent)
{
	learningResults = new QTextEdit;
	ok = new QPushButton(tr("OK"));
	save = new QPushButton(tr("Save"));
	QHBoxLayout* buttonLayer = new QHBoxLayout;
	buttonLayer->addWidget(ok);
	buttonLayer->addWidget(save);
	QVBoxLayout* qvb = new QVBoxLayout;
	qvb->addWidget(learningResults);
	qvb->addLayout(buttonLayer);
	setLayout(qvb);
	resize(400,300);
	setWindowTitle(tr("Learning Results"));
	connect(ok,SIGNAL(clicked()),this,SLOT(hideResults()));
	connect(save,SIGNAL(clicked()),this,SLOT(saveToFile()));
}

LearningStacistics::~LearningStacistics()
{
	delete learningResults;
	delete ok;
	delete save;
}

void LearningStacistics::showRessults(double *results)
{
	learningResults->clear();
	learningResults->append(tr("Iteration: \t Training Error:"));

	switch(dataSettings().EvolAlgorithm)
	{
	case EvolAlgorithm::DE:
	{
		for(int i = 0;i< dataSettings().iterations;i++)
		{
			QString qs,qs1;
			qs.setNum(i);
			qs1.setNum(results[i]);
			qs+="\t       ";
			qs+=qs1;
			learningResults->append(qs);
		}
		break;
	}
	case EvolAlgorithm::SOMA:
	{
		for(int i=0; i<dataSettings().migrations;i++)
		{
			QString qs,qs1;
			qs.setNum(i);
			qs1.setNum(results[i]);
			qs+="\t       ";
			qs+=qs1;
			learningResults->append(qs);
		}
		break;
	}
	}
	show();
}

void LearningStacistics::showQstring(QString source)
{
	learningResults->setText(source);
	show();
}
void LearningStacistics::saveToFile()
{
	 QString fileName = QFileDialog::getSaveFileName(this,
	         tr("Save Learning Results"), "",
	         tr("Address Book (*.txt);;All Files (*)"));
	 if (fileName.isEmpty())
	 {
	         return;
	 }

	 else
	 {
		 if(!fileName.contains("_learningStatistic"))
		 {
			 fileName +="_learningStatistic";
		 }
		 if(!fileName.contains(".txt"))
		 {
			 fileName +=".txt";
		 }
		 QFile file(fileName);
		 if (!file.open(QIODevice::WriteOnly))
		 {
			 QMessageBox::information(this, tr("Unable to open file"),
				 file.errorString());
			 return;
		 }
		 else
		 {
			   QTextStream stream( &file );
			   stream << learningResults->toPlainText();
			   file.close();
		 }
	 }
}
void LearningStacistics::hideResults()
{
	hide();
}

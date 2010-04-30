#ifndef NOWE_H
#define NOWE_H

#include <QtGui/QWidget>
#include "ui_nowe.h"

class nowe : public QWidget
{
    Q_OBJECT

public:
    nowe(QWidget *parent = 0);
    ~nowe();

private:
    Ui::noweClass ui;
};

#endif // NOWE_H

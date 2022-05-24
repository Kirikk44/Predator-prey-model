#ifndef HARE_H
#define HARE_H

#include "animal.h"

class Hare: public Animal
{
    Q_OBJECT
public:
    Hare();
    Hare(int x, int y);
    Hare(Type type, int x, int y);

    void move(Cell*** cells, int* mixing) override;

private:

    static const int numberOfDaysForBudding = 20;
    void AddingAdditionalInformation(QWidget* qWidget, QVBoxLayout * hBoxLayout) override;
    void getOff(Cell*** cells, int* mixing) override;

signals:
     void deathHareSignal(Hare* hare);
     void getOfHareSignal(Hare* hare);
};

#endif // HARE_H

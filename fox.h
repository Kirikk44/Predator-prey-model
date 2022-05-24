#ifndef FOX_H
#define FOX_H

#include "animal.h"
#include "hare.h"

class Fox : public Animal
{
    Q_OBJECT
public:
    Fox();
    Fox(int x, int y);
    Fox(Cell::Type type, int x, int y);

    void move(Cell*** cells, int* check) override;

    bool findHare(Cell*** cells, std::list<Hare*>& hares, int* mixing);

protected:
    void AddingAdditionalInformation(QWidget* qWidget, QVBoxLayout * hBoxLayout) override;
    void getOff(Cell*** cells, int* mixing) override;

    static const int numberOfDaysForBudding = 30;

signals:
    void deathFoxSignal(Fox* fox);
    void getOfFoxSignal(Fox* fox);
};

#endif // FOX_H

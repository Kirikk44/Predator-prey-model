#ifndef ANIMAL_H
#define ANIMAL_H

#include "cell.h"

class Animal : public Cell
{
public:
    Animal(Type type, int x, int y);
    Animal(Type type);

//    void timerStart();
    virtual void move(Cell*** cells, int* mixing) = 0;
    void setPosOnMap(int x, int y);

protected:
    int X;
    int Y;
    int satiety{200}; // 0 == смерть
    int saturation{200};
    int countCurrentDays{100};


    virtual void getOff(Cell*** cells, int* mixing) = 0;
};

#endif // ANIMAL_H

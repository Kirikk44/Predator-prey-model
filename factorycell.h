#ifndef FACTORYCELL_H
#define FACTORYCELL_H
#include "cell.h"
#include "fox.h"
#include "hare.h"
class FactoryCell
{
public:
    FactoryCell();
    Cell* getCell(Cell::Type type, int x, int y)
    {
        if (type == Cell::FOX)
            return Fox(type, x, y);
    }
};

#endif // FACTORYCELL_H

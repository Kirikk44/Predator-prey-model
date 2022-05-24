#include "animal.h"

Animal::Animal(Cell::Type type, int x, int y): Cell(type, x, y)
{

}

Animal::Animal(Cell::Type type): Cell(type)
{

}

void Animal::setPosOnMap(int x, int y)
{
    X = x;
    Y = y;
    setPos(x*Cell::size, y * Cell::size);
}

#include "fox.h"
#include "map.h"
#include <QLabel>
#include <cmath>
#include <QDebug>

Fox::Fox(): Animal(Cell::FOX)
{
    setZValue(1);
}

Fox::Fox(int x, int y): Animal(Cell::FOX, x,y)
{
    X = x/ Cell::size;
    Y = y / Cell::size;
    this->setZValue(1);
}

Fox::Fox(Cell::Type type, int x, int y): Animal(type, x,y)
{

}

void Fox::move(Cell*** cells, int* mixing)
{
    satiety-=1;
    saturation-=1;
    countCurrentDays++;
    if (satiety <= 0 || saturation <= 0)
    {
        emit Fox::deathFoxSignal(this);
        return;
    }
    int newX;
    int newY;

    if (saturation < 95)
    {
        for (int i = 0; i <= 7; i++)
        {
            switch (i) {
            case 0:
                newX = X - 1;
                newY = Y - 1;
                break;
            case 1:
                newX = X;
                newY = Y - 1;
                break;
            case 2:
                newX = X + 1;
                newY = Y - 1;
                break;
            case 3:
                newX = X - 1;
                newY = Y;
                break;
            case 4:
                newX = X + 1;
                newY = Y;
                break;
            case 5:
                newX = X - 1;
                newY = Y + 1;
                break;
            case 6:
                newX = X;
                newY = Y + 1;
                break;
            case 7:
                newX = X + 1;
                newY = Y + 1;
                break;
            }

            if (newX >= 0 && newY >= 0 && newY < Map::height && newX < Map::width)
            {
                if (cells[newY][newX]->getType() == Cell::WATER)
                {
                    saturation = 100;
                    return;
                }
            }
        }
    }
    // рандомное движение
    for(int i = 0; i <= 7; i++)
    {
        switch (mixing[i]) {
        case 0:
            newX = X - 1;
            newY = Y - 1;
            break;
        case 1:
            newX = X;
            newY = Y - 1;
            break;
        case 2:
            newX = X + 1;
            newY = Y - 1;
            break;
        case 3:
            newX = X - 1;
            newY = Y;
            break;
        case 4:
            newX = X + 1;
            newY = Y;
            break;
        case 5:
            newX = X - 1;
            newY = Y + 1;
            break;
        case 6:
            newX = X;
            newY = Y + 1;
            break;
        case 7:
            newX = X + 1;
            newY = Y + 1;
            break;
        }
        if (newX >= 0 && newY >= 0 && newY < Map::height && newX < Map::width && cells[newY][newX]->getType() == Cell::FIELD)
        {
            break;
        }

    }
    setPosOnMap(newX, newY);
    this->update();
    return;
}

bool Fox::findHare(Cell*** cells, std::list<Hare *>& hares, int* mixing) // тут можно взять Animal впринципе
{
    std::list<Hare*>::iterator it;

    if(satiety < 93)
        for (it = hares.begin(); it != hares.end(); it++)
        {
            if (std::sqrt(pow(((*it)->getX() - this->getX()), 2) + pow(((*it)->getY() - this->getY()), 2)) < 2)
            {
                qDebug() << "схавала";
                this->setPosOnMap((*it)->getX(), (*it)->getY());
                satiety = 100;
                if (countCurrentDays <= numberOfDaysForBudding)
                {
                    // отпочковаться
                    getOff(cells, mixing);
                    satiety = 50;
                }else countCurrentDays = 0;
                emit (*it)->Hare::deathHareSignal(*it);
                return true;
            }
        }
    return false;
}


void Fox::AddingAdditionalInformation(QWidget* qWidget, QVBoxLayout * hBoxLayout)
{
    QLabel* label = new QLabel("прошло дней после еды(если успеет поесть в течении " + QString::number(numberOfDaysForBudding) + " дней, то отпочкуется):" + QString::number(saturation), qWidget);
    hBoxLayout->addWidget(label);
    label = new QLabel("количество воды:" + QString::number(saturation), qWidget);
    hBoxLayout->addWidget(label);
    label = new QLabel("сытость:" + QString::number(satiety), qWidget);
    hBoxLayout->addWidget(label);
}

void Fox::getOff(Cell*** cells, int *mixing)
{
    Fox* newFox = new Fox();
    newFox->satiety = 50;
    newFox->saturation = 60;
    int newX;
    int newY; // TODO: возможно стоит написать функцию которая автоматически чекает окрестность

    for(int i = 7; i >=0; i--)
    {
        switch (mixing[i]) {
        case 0:
            newX = X - 1;
            newY = Y - 1;
            break;
        case 1:
            newX = X;
            newY = Y - 1;
            break;
        case 2:
            newX = X + 1;
            newY = Y - 1;
            break;
        case 3:
            newX = X - 1;
            newY = Y;
            break;
        case 4:
            newX = X + 1;
            newY = Y;
            break;
        case 5:
            newX = X - 1;
            newY = Y + 1;
            break;
        case 6:
            newX = X;
            newY = Y + 1;
            break;
        case 7:
            newX = X + 1;
            newY = Y + 1;
            break;
        }
        if (newX >= 0 && newY >= 0 && newY < Map::height && newX < Map::width && cells[newY][newX]->getType() == Cell::FIELD)
        {
            break;
        }
    }
    newFox->setPosOnMap(newX, newY);
    newFox->update();
    emit getOfFoxSignal(newFox);
}

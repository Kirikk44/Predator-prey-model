#include "hare.h"
#include "map.h"
#include <QRandomGenerator>
#include <QDebug>
#include <QLabel>

Hare::Hare(): Animal(Cell::HARE)
{
    this->setZValue(1);
}

Hare::Hare(int x, int y): Animal(Cell::HARE, x,y)
{
    X = x/ Cell::size;
    Y = y / Cell::size;
    this->setZValue(1);
}

Hare::Hare(Cell::Type type, int x, int y): Animal(type, x,y)
{
    X = x/ Cell::size;
    Y = y / Cell::size;
    this->setZValue(1);
}

void Hare::move(Cell*** cells, int* mixing)
{
    satiety-=1;
    saturation-=1;
    countCurrentDays++;

    if (satiety <= 0 || saturation <= 0)
    {
        emit Hare::deathHareSignal(this);
        return ;
    }

    int newX = 0;
    int newY = 0;

    Cell* waterCell{nullptr};
    Cell* foodCell{nullptr};

    if (saturation < 95 && satiety < 90)
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
                    waterCell = cells[newY][newX];
                }
                if (cells[newY][newX]->getType() == Cell::FOOD )
                {
                    foodCell = cells[newY][newX];
                }
            }
        }
        if (waterCell && saturation < 95)
        {
            if (foodCell && satiety <= saturation)
            {
                setPosOnMap(foodCell->getX(), foodCell->getY());
                satiety = std::min(satiety + 50, 100);
                if (countCurrentDays <= numberOfDaysForBudding)
                {
                    getOff(cells, mixing);
                    satiety = 50;
                }
                else countCurrentDays = 0;
                foodCell->setType(Cell::FIELD);
            }
            else
            {
            saturation = 100;
            }
            return;
        }
        else if (foodCell && satiety < 90)
        {
            setPosOnMap(foodCell->getX(), foodCell->getY());
            satiety = std::min(satiety + 50, 100);
            if (countCurrentDays <= numberOfDaysForBudding)
            {
                getOff(cells, mixing);
                satiety = 50;
            } else countCurrentDays = 0;
            foodCell->setType(Cell::FIELD);
            return;
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

void Hare::AddingAdditionalInformation(QWidget *qWidget, QVBoxLayout *hBoxLayout)
{
    QLabel* label = new QLabel("прошло дней после еды(если успеет поесть в течении " + QString::number(numberOfDaysForBudding) + " дней, то отпочкуется):" + QString::number(saturation), qWidget);
    hBoxLayout->addWidget(label);
    label = new QLabel("количество воды:" + QString::number(saturation), qWidget);
    hBoxLayout->addWidget(label);
    label = new QLabel("сытость:" + QString::number(satiety), qWidget);
    hBoxLayout->addWidget(label);
}

void Hare::getOff(Cell*** cells, int* mixing)
{
    Hare* newHare = new Hare();
    newHare->satiety = 50;
    newHare->saturation = 60;
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
    newHare->setPosOnMap(newX, newY);
    newHare->update();
    emit getOfHareSignal(newHare);
}


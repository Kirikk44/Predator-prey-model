#include "mapupdater.h"
#include <QDebug>
#include <QRandomGenerator>

MapUpdater::MapUpdater(QObject *parent) : QObject(parent)
{

}

void MapUpdater::addFox(Fox *fox)
{
    populationObservation->addFox();
    foxes.push_back(fox);
    scene->addItem(fox);
    connect(fox, &Fox::deathFoxSignal, this, &MapUpdater::deleteFox);
    connect(fox, &Fox::getOfFoxSignal, this, &MapUpdater::getOfFoxSlot);
}

void MapUpdater::addHare(Hare *hare)
{
    populationObservation->addHare();
    hares.push_back(hare);
    scene->addItem(hare);
    connect(hare, &Hare::deathHareSignal, this, &MapUpdater::deleteHare);
    connect(hare, &Hare::getOfHareSignal, this, &MapUpdater::getOfHareSlot);
}

void MapUpdater::setCells(Cell *** cells)
{
    this->cells = cells;
}

void MapUpdater::setPopulationObservation(PopulationObservation *populationObservation)
{
    this->populationObservation = populationObservation;
}

//void MapUpdater::foodIncrease()
//{
//    countFood++;
//}

void MapUpdater::setSize(int width, int height)
{
    this->height = height;
    this->width = width;
}

void MapUpdater::setScene(QGraphicsScene *scene)
{
    this->scene = scene;
}

void MapUpdater::addRandomAnimal(Cell::Type type)
{
    Animal* animal{nullptr};
    int ix, iy;
    if (type == Cell::FOX)
    {
        animal  = new Fox();
        addFox(reinterpret_cast<Fox*>(animal));
    }
    else if (type == Cell::HARE)
    {
        animal = new Hare();
        addHare(reinterpret_cast<Hare*>(animal));
    }else
    {
        return;
    }

    while(true)
    {
        ix = (QRandomGenerator::global()->generate()) % width;
        iy = (QRandomGenerator::global()->generate()) % height;
        if(cells[iy][ix]->getType() == Cell::FIELD)
        {
            animal->setPosOnMap(ix, iy);
            break;
        }
    }
}



void MapUpdater::updatingMap()
{
    std::list<Hare*>::iterator itHare;
    std::list<Hare*>::iterator itHarePrev;
    itHare = hares.begin();
    while (itHare!= hares.end())
    {
        itHarePrev = itHare;
        itHare++;
        moveHare(*itHarePrev);
    }

    std::list<Fox*>::iterator itFox;
    std::list<Fox*>::iterator itFoxPrev;
    itFox = foxes.begin();
    while(itFox != foxes.end())
    {
        itFoxPrev = itFox;
        itFox++;
        if (!(*itFoxPrev)->findHare(cells, hares, mixing))
            moveFox(*itFoxPrev);
    }
    updateFood();
    populationObservation->updatingPlot();
}

void MapUpdater::deleteHare(Hare *hare)
{
    populationObservation->deleteHare();
    std::list<Hare*>::iterator it;
    for(it = hares.begin(); it != hares.end(); it++)
    {
        if (hare == *it)
        {
            hares.erase(it);
            delete hare;
            break;
        }
    }
}

void MapUpdater::deleteFox(Fox *fox)
{
    populationObservation->deleteFox(); // TODO: сделать проверку и выкидывать исключение
    std::list<Fox*>::iterator it;
    for(it = foxes.begin(); it != foxes.end(); it++)
    {
        if (fox == *it)
        {
            foxes.erase(it);
            delete fox;
            break;
        }
    }
}

void MapUpdater::getOfHareSlot(Hare *hare)
{
    addHare(hare);
}

void MapUpdater::getOfFoxSlot(Fox *fox)
{
    addFox(fox);
}

void MapUpdater::mix()
{
//    std::mt19937 gen(rd());
    int i1, i2;
    for (int i = 0; i <= 4; i++)
    {
        i1 = (QRandomGenerator::global()->generate())%8;
        i2 = (QRandomGenerator::global()->generate())%8;
        std::swap(mixing[i1], mixing[i2]);
    }
}

void MapUpdater::moveHare(Hare *hare)
{
    mix();
    hare->move(cells, mixing);
}

void MapUpdater::moveFox(Fox *fox)
{
    mix();
    fox->move(cells, mixing);
}

void MapUpdater::updateFood()
{
//    std::mt19937 gen(rd());
    int ix, iy;
    int addCount = 3;
    int probability;
//    if (countFood + addCount > 50)
//    {
//        return;
//    }
    for(int i = 0; i < addCount; i++ )
    {
        probability = (QRandomGenerator::global()->generate()) % 100;
        ix = (QRandomGenerator::global()->generate()) % width;
        iy = (QRandomGenerator::global()->generate()) % height;
        if(cells[iy][ix]->getType() == Cell::FIELD && probability < 80)
        {
            cells[iy][ix]->setType(Cell::FOOD);
        }
    }
//    countFood += addCount;
}

bool MapUpdater::checkingNeighborhoodTForRabbit(Hare *)
{
}

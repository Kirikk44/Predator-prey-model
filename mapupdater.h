#ifndef MAPUPDATER_H
#define MAPUPDATER_H

#include <QObject>
#include "fox.h"
#include "hare.h"
#include <list>
#include <QGraphicsScene>
#include <random>
#include "populationobservation.h"

class MapUpdater : public QObject
{
    Q_OBJECT
public:
    explicit MapUpdater(QObject *parent = nullptr);

public:
    void addFox(Fox* fox);
    void addHare(Hare* fox);
    void setCells(Cell*** cells);
    void setPopulationObservation(PopulationObservation* populationObservation);
//    void foodIncrease();
    void setSize(int width, int height);
    void setScene(QGraphicsScene* scene);

    void addRandomAnimal(Cell::Type type);

public slots:
    void updatingMap();
    void deleteHare(Hare* hare);
    void deleteFox(Fox* fox);
    void getOfHareSlot(Hare* hare);
    void getOfFoxSlot(Fox* fox);

private:
    std::list<Fox*> foxes;
    std::list<Hare*> hares;

    int mixing[8] = {0,1,2,3,4,5,6,7};
    void mix();
    void moveHare(Hare* hare);
    void moveFox(Fox* fox);
    void updateFood();

    bool checkingNeighborhoodTForRabbit(Hare*);

//    int countFood{0};

    // Размеры карты
    int height;
    int width;

//    std::random_device rd;

    Cell*** cells;
    QGraphicsScene* scene;

    PopulationObservation* populationObservation;
signals:


};

#endif // MAPUPDATER_H

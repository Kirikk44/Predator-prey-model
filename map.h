#ifndef MAP_H
#define MAP_H
#include <cell.h>
#include <QGraphicsScene>
#include <fstream>
#include <QFile>
#include <QObject>
#include <QTimer>
#include "mapupdater.h"

class Map: public QObject
{
    Q_OBJECT
public:
    Map(QGraphicsScene *scene, MapUpdater* mapUpdater);

    static const int height = 900/Cell::size, width = 960/Cell::size;

    Cell*** getCells();

private:
    Cell*** cells;

    std::ifstream world;


    int current_frame_x =  0;
    int current_frame_y = 900;
};

#endif // MAP_H

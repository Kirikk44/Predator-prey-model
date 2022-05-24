#include "map.h"
#include "fox.h"
#include "hare.h"

Map::Map(QGraphicsScene *scene, MapUpdater* mapUpdater)
{
    world.open("C:/qt_project/mat_prac_4/world.txt");

    mapUpdater->setSize(width, height);
    mapUpdater->setScene(scene);

    if (!world.is_open())
    {
        return;
    }

    cells = new Cell**[height];
    for (int i = 0; i < height; i++)
    {
        cells[i] = new Cell*[width];
    }

    mapUpdater->setCells(cells);

    Fox* fox;
    Hare* hare;

    int x, y;

    char c;
    for (y = 0; y < height; y++)
    {
//        cells[i] = new Cell*[height];
        for (x = 0;  x < width + 1; x++)
        {
            c = world.get();
            switch (c) {
            case ' ':
                cells[y][x] = Cell::getCell(Cell::FIELD, x*Cell::size, y*Cell::size);
                break;
            case 'w':
                cells[y][x] = Cell::getCell(Cell::WATER, x*Cell::size, y*Cell::size);
                break;
            case 'b':
                cells[y][x] = Cell::getCell(Cell::BARRIER, x*Cell::size, y*Cell::size);
                break;
            case 'f':
                cells[y][x] = Cell::getCell(Cell::FOOD, x*Cell::size, y*Cell::size);
//                mapUpdater->foodIncrease();
                break;
            case 'F':
                cells[y][x] = Cell::getCell(Cell::FIELD, x*Cell::size, y*Cell::size);
                fox = new Fox(x*Cell::size, y*Cell::size);
//                scene->addItem(fox);
                mapUpdater->addFox(fox);
                break;
            case 'H':
                cells[y][x] = Cell::getCell(Cell::FIELD, x*Cell::size, y*Cell::size);
                hare = new Hare(x*Cell::size, y*Cell::size);
//                scene->addItem(hare);
                mapUpdater->addHare(hare);
                break;
            case '\n':
                continue;
            }
            scene->addItem(cells[y][x]);
//            current_frame_y -= Cell::size;
        }
//        current_frame_y = height*Cell::size;
//        current_frame_x += Cell::size;
    }
}

Cell ***Map::getCells()
{
    return  cells;
}

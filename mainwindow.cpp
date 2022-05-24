#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "cell.h"
#include <map.h>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
//    ui->graphicsView->setBackgroundBrush(QColor(255, 255, 255));

    scene.setSceneRect(0, 0, 950, 900);
    sceneGraph.setSceneRect(0,0,750,900);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    scene.setItemIndexMethod(QGraphicsScene::NoIndex);
    ui->graphicsView->setScene(&scene);

    timer = new QTimer();


    populationObservation = new PopulationObservation(ui->widget);
    mapUpdater = new MapUpdater();
    mapUpdater->setPopulationObservation(populationObservation);
    map = new Map(&scene, mapUpdater);
    mapUpdater->setCells(map->getCells());

    connect(timer, &QTimer::timeout, mapUpdater, &MapUpdater::updatingMap);

    timer->start(50);
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * возможно сделать поле клеточек в которых будет лежать еда и всё такое
 * класс сущности от которого пронаследовать лису и зайца
 * класс для контроля за популяцией, в нём будет работа с графиками и передача всяких параметров
 *                (продумать как параметры будут передаваться в зайцев и лису)
 * возможно стоит использовать паттерн фабричный метод(почитать про него перед создание классов)
 * подключить класс графики (и возможно стоит сделать класс для построения графика отдельно чтобы это делать не в классе
 *          контроля за популяцией)
 */


void MainWindow::on_pushButton_clicked()
{
    if (flag_pause)
    {
        timer->start();
        flag_pause = false;
    }
    else
    {
        timer->stop();
        flag_pause = true;
    }
}

void MainWindow::on_pushButton_3_clicked()
{
    mapUpdater->addRandomAnimal(Cell::HARE);
}

void MainWindow::on_pushButton_2_clicked()
{
     mapUpdater->addRandomAnimal(Cell::FOX);
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    timer->stop();
    timer->start(value);
}

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include "map.h"
#include <QTimer>
#include "mapupdater.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_horizontalSlider_valueChanged(int value);

private:
    Ui::MainWindow *ui;

    QTimer *timer;

    QGraphicsScene scene;
    QGraphicsScene sceneGraph;

    Map * map;
    MapUpdater* mapUpdater;
    PopulationObservation* populationObservation;

    bool flag_pause{0};

};
#endif // MAINWINDOW_H

#include "populationobservation.h"
#include <QDebug>

PopulationObservation::PopulationObservation()
{
}

PopulationObservation::PopulationObservation(QCustomPlot *plot)
{
    this->plot = plot;
    setRanges();
    plot->addGraph();
    plot->addGraph();
    plot->graph(1)->setPen(QPen(QColor(255, 140, 0)));
}

void PopulationObservation::addFox()
{
    countFox++;
}

void PopulationObservation::addHare()
{
    countHare++;
}

void PopulationObservation::deleteFox()
{
    countFox--;
}

void PopulationObservation::deleteHare()
{
    countHare--;
}

void PopulationObservation::setWidgetPlot(QCustomPlot *plot)
{
    this->plot = plot;
    setRanges();
    plot->addGraph();
    plot->addGraph();
    plot->graph(1)->setPen(QPen(QColor(255, 140, 0)));
}

void PopulationObservation::updatingPlot()
{
    countDays++;
//    qDebug() << "номер дня: " << countDays;
//    qDebug() << "количество кроликов" << countHare;
//    qDebug() << "количество лис" << countFox;
    if (countDays > N)
    {
                xBegin = countDays - N;
                xEnd = countDays;
                setRanges();
    }
    plot->graph(0)->addData(countDays, countHare);
    plot->graph(1)->addData(countDays, countFox);
    plot->replot();
}

void PopulationObservation::setRanges()
{
    plot->xAxis->setRange(xBegin, xEnd);
    plot->yAxis->setRange(0,120);
}

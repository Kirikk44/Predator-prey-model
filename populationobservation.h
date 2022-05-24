#ifndef POPULATIONOBSERVATION_H
#define POPULATIONOBSERVATION_H

#include "qcustomplot.h"

class PopulationObservation
{
public:
    PopulationObservation();
    PopulationObservation(QCustomPlot* plot);

    void addFox();
    void addHare();

    void deleteFox();
    void deleteHare();

    void setWidgetPlot(QCustomPlot* plot);

    void updatingPlot();

private:
    int N = 100;

    int countHare{0};
    int countFox{0};
    int countDays{0};

    int xBegin{0};
    int xEnd{N};

    void setRanges();

    QCustomPlot* plot;
};

#endif // POPULATIONOBSERVATION_H

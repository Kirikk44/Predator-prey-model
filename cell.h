#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include <QObject>
#include <map>
#include <QColor>
#include <QGraphicsSceneMouseEvent >
#include <QMessageBox>
#include <QVBoxLayout>
#include <QWidget>

class Cell : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    enum Type {FIELD, FOOD, WATER, BARRIER, FOX, HARE};
    static const int size = 20;
    Cell(Cell::Type type);
    Cell(Cell::Type type, int x, int y);

    int getX();
    int getY();

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void setType(Cell::Type type);
    const Type& getType(){return typecell;}

    static Cell* getCell(Type typem, int x, int y);

    void mousePressEvent(QGraphicsSceneMouseEvent  *event) override;
protected:
    Cell(QColor* color){this->color = color;};

    virtual void displaingInformation();
    virtual void AddingAdditionalInformation(QWidget* qWidget, QVBoxLayout * vBoxLayout);

    const QColor* color;
    Cell::Type typecell{FIELD};

//    static std::map<Cell::Type, const QColor> colors;

};

#endif // CELL_H

//std::map<Cell::Type, const QColor> Cell::colors{{Cell::Type::FIELD,QColor(144, 238, 144)},
//                                                      {Type::BARRIER, QColor(128, 128, 0)},
//                                                      {Type::FOOD, QColor(0, 128, 0)},
//                                                      {Type::WATER, QColor(65,105,225)},
//                                                      {Type::FOX, QColor(255, 140, 0)},
//                                                      {Type::HARE, QColor(192, 192, 192)},};

//static constexpr const QColor colors[] = {QColor(144, 238, 144), QColor(128, 128, 0), QColor(0, 128, 0), QColor(65,105,225), QColor(255, 140, 0), QColor(192, 192, 192)};

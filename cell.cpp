#include "cell.h"
#include <fox.h>
#include <hare.h>

#include <QPainter>
#include <QLabel>
#include <QButtonGroup>


Cell::Cell(Cell::Type type) {
    this->typecell = type;
    switch (type) {
    case Type::BARRIER:
        color = new QColor(128, 128, 0);
        break;
    case Type::FIELD:
        color = new QColor(144, 238, 144);
        break;
    case Type::FOOD:
        color = new QColor(0, 128, 0);
        break;
    case Type::FOX:
        color = new QColor(255, 140, 0);
        break;
    case Type::HARE:
        color = new QColor(192, 192, 192);
        break;
    case Type::WATER:
        color = new QColor(65,105,225);
        break;
    }
};

Cell::Cell(Cell::Type type, int x, int y) {
    this->typecell = type;
//    color = &colors[typecell];
    this->setPos(x, y);
    switch (type) {
    case Type::BARRIER:
        color = new QColor(34, 139, 34);
        break;
    case Type::FIELD:
        color = new QColor(144, 238, 144);
        break;
    case Type::FOOD:
        color = new QColor(255, 182, 193);
        break;
    case Type::FOX:
        color = new QColor(255, 140, 0);
        break;
    case Type::HARE:
        color = new QColor(192, 192, 192);
        break;
    case Type::WATER:
        color = new QColor(65,105,225);
        break;
    }
}

int Cell::getX()
{
    return this->x()/Cell::size;
}

int Cell::getY()
{
    return this->y()/Cell::size;
};

QRectF Cell::boundingRect() const
{
    return QRectF(0, 0, size, size);
}

void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setRenderHint(QPainter::TextAntialiasing, true);

    painter->setBrush(*color);
    painter->setPen(QColor(105, 105, 105));
    painter->drawRect(0,0,size,size);
}

void Cell::setType(Cell::Type type)
{
    this->typecell = type;
    switch (type) {
    case Type::BARRIER:
        color = new QColor(34, 139, 34);
        break;
    case Type::FIELD:
        color = new QColor(144, 238, 144);
        break;
    case Type::FOOD:
        color = new QColor(255, 182, 193);
        break;
    case Type::FOX:
        color = new QColor(255, 140, 0);
        break;
    case Type::HARE:
        color = new QColor(192, 192, 192);
        break;
    case Type::WATER:
        color = new QColor(65,105,225);
        break;
    }
    this->update();
}

Cell* Cell::getCell(Type type, int x, int y)
{
    if (type == Type::FOX)
        return new Fox(type, x, y);
    else if(type == Type::HARE)
        return new Hare(type, x, y);
    else
        return new Cell(type, x, y);
}

#include <QDebug>
void Cell::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        qDebug() << "тыкнул";
        displaingInformation();
        event->accept();
    }
    //    event->ignore();
}

void Cell::displaingInformation()
{
    QWidget* window = new QWidget();
    window->setGeometry(400,400, 200, 200);
    QVBoxLayout *layout = new QVBoxLayout();

    QLabel* label1 = new QLabel(window);

    switch (typecell) {
    case Type::BARRIER:
        label1->setText("Тип ячейки: Лес");
        break;
    case Type::FIELD:
        label1->setText("Тип ячейки: Поле");
        break;
    case Type::FOOD:
        label1->setText("Тип ячейки: Еда");
        break;
    case Type::WATER:
        label1->setText("Тип ячейки: Вода");
        break;
    case Type::FOX:
        label1->setText("Тип ячейки: Лиса");
        break;
    case Type::HARE:
        label1->setText("Тип ячейки: Заяц");
        break;
    }
    AddingAdditionalInformation(window, layout);
    layout->addWidget(label1);

    layout->setDirection(QVBoxLayout::BottomToTop);

    window->setLayout(layout);

    window->show();
}

void Cell::AddingAdditionalInformation(QWidget *qWidget, QVBoxLayout *hBoxLayout)
{

}

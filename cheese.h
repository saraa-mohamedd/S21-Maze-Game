#ifndef CHEESE_H
#define CHEESE_H
#include <QGraphicsPixmapItem>

class Cheese : public QGraphicsPixmapItem
{
public:
    Cheese();
    Cheese(int initialRow, int initialColumn);
    void Adjustposition(int row, int column);
};

#endif // CHEESE_H

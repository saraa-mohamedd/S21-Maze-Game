#ifndef CHEESE_H
#define CHEESE_H
#include<iostream>
#include <QGraphicsPixmapItem>

class Cheese : public QGraphicsPixmapItem
{
public:
    Cheese(int initialRow, int initialColumn);
    void Adjustposition(int row, int column);
};

#endif // CHEESE_H

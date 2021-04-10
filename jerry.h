#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include "cheese.h"

class Jerry : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    char direction;
    int row, column;
    int data[13][13];
    int lives;
    bool holdingCheese;
    bool invincibleMode;
    int numCheeseinHome;
public:
    Jerry(int initialRow, int initialColumn, int d[13][13]);
    void setRow(int newRow);
    int getRow();
    void setColumn(int newColumn);
    int getColumn();
    //void cheeseCollision(QGraphicsItem &c);
public slots:
    void keyPressEvent(QKeyEvent* event);
    void move();

};

#endif // JERRY_H

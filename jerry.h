#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>
#include <QTimer>
#include <QTimerEvent>
#include <QGraphicsTextItem>
#include "cheese.h"
#include "pellets.h"

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
    QGraphicsItem* currentcheese;
    QGraphicsTextItem livesOnScreen;
    QGraphicsTextItem modeOnScreen;
    QTimer timer;

public:
    Jerry(int initialRow, int initialColumn, int d[13][13], QGraphicsScene* s);
    void setRow(int newRow);
    int getRow();
    void setColumn(int newColumn);
    int getColumn();
    void cheeseCollision(QGraphicsItem* c);
    void cheeseBackHome();
public slots:
    void keyPressEvent(QKeyEvent* event);
    void move();
    void pelletCollision();

};

#endif // JERRY_H

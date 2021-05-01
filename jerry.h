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
#include "tom.h"

class Jerry : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    char direction;                                      //the direction moved
    int row, column;                                     //current row and column numbers
    int data[13][13];                                    //file with board info
    int lives=3;                                         //jerry's current lives (initialized with 3)
    bool holdingCheese;                                  //whether currently holding cheese or not
    bool invincibleMode;                                 //whether current mode is invincible or not
    int numCheeseinHome;                                 //number of cheeses currently in home
    QGraphicsItem* currentcheese;                        //pointer to the cheese currently in jerry's hand
    QGraphicsTextItem livesOnScreen;                     //display of lives on screen
    QGraphicsTextItem modeOnScreen;                      //display of mode on screen
    QGraphicsTextItem jerryLostOnScreen;                 //display of game over screen
    QGraphicsTextItem jerryWonOnScreen;                  //display of victory on screen
    QGraphicsItem* Tom;                                  //pointer to tom on board
    QTimer timer;                                        //timer for invincible mode timeout
public:
    Jerry(int initialRow, int initialColumn, int d[13][13], QGraphicsScene* s);
    void setRow(int newRow);
    int getRow();
    void setColumn(int newColumn);
    int getColumn();
    void cheeseCollision(QGraphicsItem* c);
    void cheeseBackHome();
    void livescounter();
    void pelletCollision(QGraphicsItem* p);
    void gameover();
    void victory();
public slots:
    void keyPressEvent(QKeyEvent* event);
    void move();
    void pelletCollisionOver();
    void tomCollision();

};

#endif // JERRY_H

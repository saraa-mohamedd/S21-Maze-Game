#ifndef JERRY_H
#define JERRY_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QKeyEvent>
#include <QList>
#include <QGraphicsScene>

class Jerry : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
private:
    char direction;
    int row, column;
    int data[13][13];
public:
    Jerry(int initialRow, int initialColumn, int d[13][13]);
    void setRow(int newRow);
    int getRow();
    void setColumn(int newColumn);
    int getColumn();
public slots:
};

#endif // JERRY_H

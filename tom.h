#ifndef TOM_H
#define TOM_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QTimerEvent>
#include <QList>

class tom : public QObject, public QGraphicsPixmapItem
{
 Q_OBJECT
private:
    int row, column;
    int data[13][13];
public:
    tom(int d[13][13]);
public slots:
    void chase();
};

#endif // TOM_H

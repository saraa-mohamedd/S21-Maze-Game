#ifndef TOM_H
#define TOM_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QTimerEvent>
#include <QList>
#include<jerry.h>
#include<vector>
using namespace std;
const int INFINITE = 999;
const int COUNT = 13;

class tom : public QObject, public QGraphicsPixmapItem
{
 Q_OBJECT
private:
    int row, column;
    int data[13][13];
    int adjm[76][76];
    int tomnode;





public:
    tom(int d[13][13]);
    vector<vector<int>> Dijkstra(int Graph[COUNT][COUNT],int tnode,int jnode);
public slots:
    void chase();

};

#endif // TOM_H

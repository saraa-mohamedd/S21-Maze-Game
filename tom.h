#ifndef TOM_H
#define TOM_H
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QTimerEvent>
#include <QList>
#include <vector>
#include "jerry.h"
using namespace std;
const int INFINITE = 999;
const int COUNT = 76;

class tom : public QObject, public QGraphicsPixmapItem
{
 Q_OBJECT
private:
    int row, column;
    int jerryrow, jerrycolumn;
    int data[13][13];
    int adjm[76][76];
    int tomnode;
    int jerrynode;
    class Jerry* j1;
public:
    tom(int d[13][13], class Jerry* jry);
    vector<int> Dijkstra(int Graph[COUNT][COUNT],int tnode,int jnode);
    void jerrypos(int jrow, int jcolmn);
public slots:
    void chase();
};

#endif // TOM_H

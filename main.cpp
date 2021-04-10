    #include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "jerry.h"
#include "cheese.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QGraphicsView view;
    QGraphicsScene scene;

    view.setFixedSize(750, 750);
    view.setWindowTitle("Maze Game");
    view.setBackgroundBrush(QBrush(Qt::black));

    int boardData[13][13];
    QFile file("board.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
            stream >> boardData[i][j];

    QPixmap wallImage("wall.jpg"), floorImage("floor.jpg");
    wallImage = wallImage.scaledToWidth(50);
    wallImage = wallImage.scaledToHeight(50);
    floorImage = floorImage.scaledToWidth(50);
    floorImage = floorImage.scaledToHeight(50);
    QGraphicsPixmapItem boardImages[13][13];
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
        {
            // Set Image
            if (boardData[i][j] == -1)
                boardImages[i][j].setPixmap(wallImage);
            else
                boardImages[i][j].setPixmap(floorImage);
            // Set Position
            boardImages[i][j].setPos(50 + 50 * j, 50 + 50 * i);
            // Add to the Scene
            scene.addItem(&boardImages[i][j]);
        }

    Jerry j(6,6,boardData);
    scene.addItem(&j);

    Cheese c1(1, 1);
    Cheese c2(1, 11);
    Cheese c3(11, 1);
    Cheese c4(11, 11);

    scene.addItem(&c1);
    scene.addItem(&c2);
    scene.addItem(&c3);
    scene.addItem(&c4);

    view.setScene(&scene);
    view.show();
    return a.exec();
}

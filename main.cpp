#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QFile>
#include <QTextStream>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "jerry.h"
#include "tom.h"

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

    QPixmap wallImage("wall.jpg"), floorImage("floor.jpeg"), rug1("homee1.png"), rug2("homee2.png"), rug3("homee3.png"),plate("plate.jpg");
    wallImage = wallImage.scaledToWidth(50);
    wallImage = wallImage.scaledToHeight(50);
    floorImage = floorImage.scaledToWidth(50);
    floorImage = floorImage.scaledToHeight(50);
    rug1 = rug1.scaledToWidth(75);
    rug1 = rug1.scaledToHeight(57);
    rug2 = rug2.scaledToWidth(75);
    rug2 = rug2.scaledToHeight(55);
    rug3 = rug3.scaledToWidth(75);
    rug3 = rug3.scaledToHeight(57);
    plate= plate.scaledToWidth(50);
    plate= plate.scaledToHeight(50);
    QGraphicsPixmapItem boardImages[13][13];
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
        {
            // Set Image
            if (boardData[i][j] == -1)
                boardImages[i][j].setPixmap(wallImage);
            else if (boardData[i][j] == 36)
                boardImages[i][j].setPixmap(rug1);
            else if (boardData[i][j] == 37)
                boardImages[i][j].setPixmap(rug2);
            else if (boardData[i][j] == 38)
                boardImages[i][j].setPixmap(rug3);
            else if (boardData[i][j] == 27 || boardData[i][j] == 44 || boardData[i][j] == 46 ||  boardData[i][j] == 29)
                boardImages[i][j].setPixmap(plate);
            else
                boardImages[i][j].setPixmap(floorImage);
            // Set Position
            boardImages[i][j].setPos(50 + 50 * j, 50 + 50 * i);
            // Add to the Scene
            scene.addItem(&boardImages[i][j]);
        }


    Cheese c1(1, 1);
    Cheese c2(1, 11);
    Cheese c3(11, 1);
    Cheese c4(11, 11);
    scene.addItem(&c1);
    scene.addItem(&c2);
    scene.addItem(&c3);                             //creating four cheese objects and adding them to the scene
    scene.addItem(&c4);                             //in the four corners of the maze

    Pellets p1(1, 4);
    Pellets p2(9, 9);
    scene.addItem(&p1);                             //initializing pellets and adding to scene
    scene.addItem(&p2);                             //in chosen positions

    Jerry j(6,6,boardData, &scene);
    scene.addItem(&j);
    tom t(boardData, &j);
    scene.addItem(&t);                                //adding jerry and tom to scene

    j.setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    j.setFocus();
    QTimer timer;
    timer.start(70);                                //adjusting and setting timer for jerry's motion
    timer.connect(&timer, SIGNAL(timeout()), &j, SLOT(move()));

    QTimer ttimer;
    ttimer.start(50000);                             //adjusting and starting timer for tom's motion
    ttimer.connect(&timer, SIGNAL(timeout()), &t, SLOT(chase()));
    view.setScene(&scene);
    view.show();

    return a.exec();
}

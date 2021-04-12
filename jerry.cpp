#include "jerry.h"
#include <QDebug>
Jerry::Jerry(int initialRow, int initialColumn, int d[13][13])
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
            data[i][j] = d[i][j];
    // Set Image
    QPixmap image("jerry.png");
    image = image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);
    // Set Position
    setPos(50 + 50 * initialColumn, 50 + 50 * initialRow);
    row = initialRow;
    column = initialColumn;

/*
    livesOnScreen.setPlainText("lives: 3");
    livesOnScreen.setDefaultTextColor(QColor(0, 1, 0, 225));
    livesOnScreen.setX(200);
    livesOnScreen.setY(200);
    scene()->addItem(&livesOnScreen);
*/

    lives = 3;
    holdingCheese = false;
    invincibleMode = false;
    currentcheese = NULL;
    numCheeseinHome = 0;
}

void Jerry::setRow(int newRow)
{
    row = newRow;
}

int Jerry::getRow()
{
    return row;
}

void Jerry::setColumn(int newColumn)
{
    column = newColumn;
}

int Jerry::getColumn()
{
    return column;
}

void Jerry::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Up)
    {
        direction = 'u';
    }
    else if (event->key() == Qt::Key_Down)
    {
        direction = 'd';
    }
    else if (event->key() == Qt::Key_Right)
    {
        direction = 'r';
    }
    else if (event->key() == Qt::Key_Left)
    {
        direction = 'l';
    }
}
void Jerry::move()
{
    if (direction == 'u' && data[row - 1][column] != -1)
    {
        row--;
    }
    else if (direction == 'd' && data[row + 1][column] != -1)
    {
        row++;
    }
    else if (direction == 'r' && data[row][column + 1] != -1)
    {
        column++;
    }
    else if (direction == 'l' && data[row][column - 1] != -1)
    {
        column--;
    }
    setPos(50 + 50 * column, 50 + 50 * row);

    QList<QGraphicsItem*> items = collidingItems();
    for (int i = 0; i < items.size(); i++)
    {
        if (typeid(*(items[i])) == typeid(Cheese))
        {
            if ((row==5 && column==5)||(row==5 && column==7)||(row==7 && column==5)||(row==7 && column==7))
            {}
            else
            { cheeseCollision(items[i]); }
        }
        else if (typeid(*(items[i])) == typeid(Pellets))
        {
            timer.start(5000);
            scene()->removeItem(items[i]);
            QPixmap image("tom.png");
            image = image.scaledToWidth(50);
            image = image.scaledToHeight(50);
            setPixmap(image);
            invincibleMode = true;
            timer.connect(&timer, SIGNAL(timeout()), this, SLOT(pelletCollision()));
        }

    }

    if (((row == 5 && column == 6) || (row == 7 && column == 6) || (row == 6 && column == 5) || (row == 6 && column == 7))
        && (currentcheese != NULL))
    {
        cheeseBackHome();
    }
}

void Jerry::cheeseCollision(QGraphicsItem* c)
{
    if (holdingCheese)
       return;
     else
     {
       holdingCheese = true;
       currentcheese = c;
       scene()->removeItem(c);
       QPixmap image("jerry cheese.png");
       image = image.scaledToWidth(50);
       image = image.scaledToHeight(50);
       setPixmap(image);
     }
}

void Jerry::cheeseBackHome()
{
    QPixmap image("jerry.png");
    image = image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);
    numCheeseinHome++;
    if (numCheeseinHome == 1)
    {
        (*currentcheese).setPos(50 + 50 * 5, 50 + 50 * 5);
        scene()->addItem(currentcheese);
    }
    else if (numCheeseinHome == 2)
    {
        (*currentcheese).setPos(50 + 50 * 7, 50 + 50 * 5);
        scene()->addItem(currentcheese);
    }
    else if (numCheeseinHome == 3)
    {
        (*currentcheese).setPos(50 + 50 * 5, 50 + 50 * 7);
        scene()->addItem(currentcheese);
    }
    else if (numCheeseinHome == 4)
    {
        (*currentcheese).setPos(50 + 50 * 7, 50 + 50 * 7);
        scene()->addItem(currentcheese);
    }
    holdingCheese = false;
    currentcheese = NULL;
}

void Jerry::pelletCollision()
{
    invincibleMode = false;
    QPixmap image("jerry.png");
    image = image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);
    return;
}

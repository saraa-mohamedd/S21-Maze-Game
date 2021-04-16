#include "jerry.h"
#include <QDebug>
Jerry::Jerry(int initialRow, int initialColumn, int d[13][13], QGraphicsScene* s)
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
            data[i][j] = d[i][j];
    // Set Image
    QPixmap image("/Users/layla/desktop/jerry.png");
    image = image.scaledToWidth(45);
    image = image.scaledToHeight(45);
    setPixmap(image);
    // Set Position
    setPos(50 + 50 * initialColumn, 50 + 50 * initialRow);
    row = initialRow;
    column = initialColumn;

    QFont* f = new QFont;
    f->setPointSize(15);
    f->setBold(true);
    livescounter();
    livesOnScreen.setDefaultTextColor(QColor(255, 255, 255, 225));
    livesOnScreen.setX(50);
    livesOnScreen.setY(15);
    livesOnScreen.setFont(*f);
    livesOnScreen.adjustSize();

    modeOnScreen.setPlainText("MODE: REGULAR");
    modeOnScreen.setDefaultTextColor(QColor(255, 255, 0, 225));
    modeOnScreen.setX(550);
    modeOnScreen.setY(15);
    modeOnScreen.setFont(*f);
    modeOnScreen.adjustSize();
    // adjusting text on screen

    s->addItem(&modeOnScreen);
    s->addItem(&livesOnScreen);
    // adding text to screen
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
        if(!holdingCheese && !invincibleMode)
        {
        QPixmap image("/Users/layla/desktop/jerry.png");
        image = image.scaledToWidth(45);
        image = image.scaledToHeight(45);
        setPixmap(image);
        }
        else if(holdingCheese && !invincibleMode)
        {
            QPixmap image("/Users/layla/desktop/jerry cheese.png");
            image = image.scaledToWidth(55);
            image = image.scaledToHeight(55);
            QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
            setPixmap(reflectedimage);
         }
        else if(invincibleMode && !holdingCheese)
        {
            QPixmap image("/Users/layla/desktop/jerry trans.png");
            image = image.scaledToWidth(45);
            image = image.scaledToHeight(45);
            setPixmap(image);
         }
        else if(invincibleMode && holdingCheese)
        {
            QPixmap image("/Users/layla/desktop/jerry cheese trans.png");
            image = image.scaledToWidth(55);
            image = image.scaledToHeight(55);
            QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
            setPixmap(reflectedimage);
         }
    }
    else if (direction == 'l' && data[row][column - 1] != -1)
    {
        column--;
        if(!holdingCheese && !invincibleMode)
         {
        QPixmap image("/Users/layla/desktop/jerry.png");
        image = image.scaledToWidth(45);
        image = image.scaledToHeight(45);
        QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
        setPixmap(reflectedimage);
        }
        else if(holdingCheese && !invincibleMode)
        {
            QPixmap image("/Users/layla/desktop/jerry cheese.png");
            image = image.scaledToWidth(55);
            image = image.scaledToHeight(55);
            setPixmap(image);
        }
        else if(invincibleMode && !holdingCheese)
        {
            QPixmap image("/Users/layla/desktop/jerry trans.png");
            image = image.scaledToWidth(45);
            image = image.scaledToHeight(45);
            QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
            setPixmap(reflectedimage);
        }
        else if(invincibleMode && holdingCheese)
        {
            QPixmap image("/Users/layla/desktop/jerry cheese trans.png");
            image = image.scaledToWidth(55);
            image = image.scaledToHeight(55);
            setPixmap(image);
        }
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
            if(!holdingCheese)
            {
            QPixmap image("/Users/layla/desktop/jerry trans.png");
            image = image.scaledToWidth(45);
            image = image.scaledToHeight(45);
            setPixmap(image);
            }
            else
            {
                QPixmap image("/Users/layla/desktop/jerry cheese trans.png");
                image = image.scaledToWidth(55);
                image = image.scaledToHeight(55);
                setPixmap(image);
            }
            modeOnScreen.setTextWidth(210);
            modeOnScreen.setX(515);
            modeOnScreen.setPlainText("MODE: INVINCIBLE");
            invincibleMode = true;
            timer.connect(&timer, SIGNAL(timeout()), this, SLOT(pelletCollision()));
        }
         else if (typeid(*(items[i])) == typeid(tom))
        {
            if(!invincibleMode)
            {
            QPixmap image("/Users/layla/desktop/tomcaught.png");
            image = image.scaledToWidth(50);
            image = image.scaledToHeight(50);
            setPixmap(image);
            caught = true;
            tomCollision();
            }
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
       if(!invincibleMode)
       {
       QPixmap image("/Users/layla/desktop/jerry cheese.png");
       image = image.scaledToWidth(55);
       image = image.scaledToHeight(55);
       setPixmap(image);
       }
       else
       {
           QPixmap image("/Users/layla/desktop/jerry cheese trans.png");
           image = image.scaledToWidth(55);
           image = image.scaledToHeight(55);
           setPixmap(image);
       }
     }
}

void Jerry::cheeseBackHome()
{
    QPixmap image("/Users/layla/desktop/jerry.png");
    image = image.scaledToWidth(45);
    image = image.scaledToHeight(45);
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
    QPixmap image("/Users/layla/desktop/jerry.png");
    modeOnScreen.setX(550);
    modeOnScreen.setTextWidth(178);
    modeOnScreen.setPlainText("MODE: REGULAR");
    image = image.scaledToWidth(45);
    image = image.scaledToHeight(45);
    setPixmap(image);
    return;
}
void Jerry::tomCollision()
{
    int initialrow = 6, initialcolumn = 6;
    if(caught)
    {
        if(holdingCheese)
        {
            //return cheese to starting point

        }
        //return jerry to home
        QPixmap image("/Users/layla/desktop/jerry.png");
        image = image.scaledToWidth(45);
        image = image.scaledToHeight(45);
        setPixmap(image);
        // Set Position
        setPos(50 + 50 * initialrow, 50 + 50 * initialcolumn);
        row = initialrow;
        column = initialcolumn;
        lives--;
        livescounter();
    }
}
int Jerry::livescounter()
{
    if (lives==3)
    livesOnScreen.setPlainText("LIVES: 3");
    else if(lives==2)
    livesOnScreen.setPlainText("LIVES: 2");
    else if(lives==1)
    livesOnScreen.setPlainText("LIVES: 1");
    else if(lives==0)
    {
        livesOnScreen.setPlainText(" ");
    //end game + game over screen
    }
    return lives;
}

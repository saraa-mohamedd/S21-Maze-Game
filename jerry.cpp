#include "jerry.h"
#include <QDebug>

Jerry::Jerry(int initialRow, int initialColumn, int d[13][13], QGraphicsScene* s)
{
    for (int i = 0; i < 13; i++)
        for (int j = 0; j < 13; j++)
            data[i][j] = d[i][j];
    // Set Image
    QPixmap image("jerry.png");
    image = image.scaledToWidth(45);
    image = image.scaledToHeight(45);
    setPixmap(image);
    // Set Position
    setPos(50 + 50 * initialColumn, 50 + 50 * initialRow);
    row = initialRow;
    column = initialColumn;

    QFont* f = new QFont;
    f->setPointSize(15);                                       //initializing QFont to be used for
    f->setBold(true);                                          //display of lives and mode on screen

    livescounter();                                            //calling function that manages text of livesOnScreen
    livesOnScreen.setDefaultTextColor(QColor(255, 255, 0, 225));
    livesOnScreen.setX(50);
    livesOnScreen.setY(15);
    livesOnScreen.setFont(*f);                                  //adjusting text for lives on screen
    livesOnScreen.adjustSize();

    modeOnScreen.setPlainText("MODE: REGULAR");
    modeOnScreen.setDefaultTextColor(QColor(255, 255, 0, 225));
    modeOnScreen.setX(520);
    modeOnScreen.setY(15);
    modeOnScreen.setFont(*f);                                   //adjusting text for game mode on screen
    modeOnScreen.adjustSize();

    s->addItem(&modeOnScreen);
    s->addItem(&livesOnScreen);                                 //adding to scene the two QGraphicsPlainText objects

    holdingCheese = false;
    invincibleMode = false;
    currentcheese = NULL;                                       //initializing conditions of jerry
    numCheeseinHome = 0;                                        //and cheeses across board
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
            QPixmap image("jerry.png");
            image = image.scaledToWidth(45);                        //adjusting pic of jerry according to different
            image = image.scaledToHeight(45);                       //conditions (invincible mode and holding
            setPixmap(image);                                       //cheese) and setting it to appropriate pic
        }
        else if(holdingCheese && !invincibleMode)
        {
            QPixmap image("jerry cheese.png");
            image = image.scaledToWidth(55);
            image = image.scaledToHeight(55);
            QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
            setPixmap(reflectedimage);
         }
        else if(invincibleMode && !holdingCheese)
        {
            QPixmap image("jerry trans.png");
            image = image.scaledToWidth(45);
            image = image.scaledToHeight(45);
            setPixmap(image);
         }
        else if(invincibleMode && holdingCheese)
        {
            QPixmap image("jerry cheese trans.png");
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
            QPixmap image("jerry.png");                             //adjusting pic of jerry according to different
            image = image.scaledToWidth(45);                        //conditions again, but flipping image
            image = image.scaledToHeight(45);                       //when direction becomes left and not right
            QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
            setPixmap(reflectedimage);
        }
        else if(holdingCheese && !invincibleMode)
        {
            QPixmap image("jerry cheese.png");
            image = image.scaledToWidth(55);
            image = image.scaledToHeight(55);
            setPixmap(image);
        }
        else if(invincibleMode && !holdingCheese)
        {
            QPixmap image("jerry trans.png");
            image = image.scaledToWidth(45);
            image = image.scaledToHeight(45);
            QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
            setPixmap(reflectedimage);
        }
        else if(invincibleMode && holdingCheese)
        {
            QPixmap image("jerry cheese trans.png");
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
            {}                                              //not allowing cheeseCollision to be carried out
                                                            //if collision is with cheese already inside home
            else
            { cheeseCollision(items[i]); }
        }
        else if (typeid(*(items[i])) == typeid(Pellets))
        {
            if (!invincibleMode)
            {
                QSound::play("powerup.wav");
                pelletCollision(items[i]);                       //carrying out pelletCollision if mode isn't already
                                                                 //invincible and collision with pellet occurs
            }

        }
        else if (typeid(*(items[i])) == typeid(tom))
        {
            Tom=items[i];
            tomCollision();                                  //collision with tom called and tom saved to Tom variable
        }
    }

    if (((row == 5 && column == 6) || (row == 7 && column == 6) || (row == 6 && column == 5) || (row == 6 && column == 7))
        && (currentcheese != NULL))
    {
        cheeseBackHome();                                    //cheeseBackHome called if jerry is at doors of home
                                                             //and is holding cheese (currentcheese isn't null)
    }
}

void Jerry::cheeseCollision(QGraphicsItem* c)
{
    if (holdingCheese)
       return;
     else
     {
       QSound::play("cheese.wav");
       holdingCheese = true;
       currentcheese = c;
       scene()->removeItem(c);                              //adjusts variables to hold cheese
       if(!invincibleMode)
       {
           QPixmap image("jerry cheese.png");
           image = image.scaledToWidth(55);
           image = image.scaledToHeight(55);                //changing picture of jerry to appropriate pic
           setPixmap(image);                                //(to look like he's holding a cheese)
       }
       else
       {
           QPixmap image("jerry cheese trans.png");
           image = image.scaledToWidth(55);
           image = image.scaledToHeight(55);                //changing pic of jerry to appropriate pic
           setPixmap(image);                                //but in the invincible mode condition (diff pic)
       }
     }
}

void Jerry::cheeseBackHome()
{
    QPixmap image("jerry.png");
    image = image.scaledToWidth(45);
    image = image.scaledToHeight(45);
    setPixmap(image);                                        //changes picture back to original pic (not holding cheese)
    numCheeseinHome++;                                       //increases number of cheese in home by one
    if (numCheeseinHome == 1)
    {
        (*currentcheese).setPos(50 + 50 * 5, 50 + 50 * 5);
        scene()->addItem(currentcheese);                     //sets currentcheese to position in home depending
    }                                                        //on current amount of cheeses in home
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
        victory();                                           //calls function to display victory message if 4 cheese
    }                                                        //are home (winning condition met)
    holdingCheese = false;
    currentcheese = NULL;                                    //sets modes back to no longer holding cheese
}

void Jerry::pelletCollision(QGraphicsItem* p)
{
    timer.start(5000);
    scene()->removeItem(p);                                 //removes pellet from scene
    if(!holdingCheese)
    {
        QPixmap image("jerry trans.png");
        image = image.scaledToWidth(45);
        image = image.scaledToHeight(45);                   //adjusts picture to invincible mode picture
        setPixmap(image);
    }
    else
    {
        QPixmap image("jerry cheese trans.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);                   //adjusts picture to invincible mode picture
        setPixmap(image);                                   //for holding cheese condition
    }
    modeOnScreen.setTextWidth(210);
    modeOnScreen.setX(490);
    modeOnScreen.setPlainText("MODE: INVINCIBLE");          //changes text on screen to become invincible
    invincibleMode = true;                                  // and sets invincibleMode to be true
    timer.connect(&timer, SIGNAL(timeout()), this, SLOT(pelletCollisionOver()));
}                                                           //starts timer for invincible mode duration

void Jerry::pelletCollisionOver()
{
    invincibleMode = false;                                 //sets invincibleMode back to false
    if(holdingCheese)
    {
        QPixmap image("jerry cheese.png");
        image = image.scaledToWidth(45);
        image = image.scaledToHeight(45);                   //adjusts pic back to original
        setPixmap(image);                                   //(not inivincible mode)
    }
    else
    {
        QPixmap image("jerry.png");
        image = image.scaledToWidth(45);
        image = image.scaledToHeight(45);                   //adjusts pic back
        setPixmap(image);                                   //to original
    }
    modeOnScreen.setX(520);
    modeOnScreen.setTextWidth(178);
    modeOnScreen.setPlainText("MODE: REGULAR");             //sets text back to say regular mode

    return;
}

void Jerry::livescounter()
{
    if (lives==3)
    livesOnScreen.setPlainText("LIVES: 3");                 //adjusts livesOnScreen depending on lives remaining
    else if(lives==2)
    livesOnScreen.setPlainText("LIVES: 2");
    else if(lives==1)
    livesOnScreen.setPlainText("LIVES: 1");
    else if(lives==0)
    {
        livesOnScreen.setPlainText("LIVES: 0");
        gameover();                                         //calls gameover when zero lives remain
    }
}

void Jerry::tomCollision()
{
    if(!invincibleMode)
    {
        QSound::play("caught.wav");

        row = 6;
        column = 6;                                         //sets row and column back to original (6 and 6)
        direction = ' ';                                    //and makes him stay still
        setPos(50 + 50 * row, 50 + 50 * column);            //sets jerry position back to center of board
        lives--;                                            //and decreases his lives by one
        livescounter();                                     //calling livescounter to manage display
        if(holdingCheese)
        {
            scene()->addItem(currentcheese);                //if holding cheese when caught, returns it back
            currentcheese = NULL;
            holdingCheese = false;                          //and sets conditions to no cheese in hand
            QPixmap image("jerry.png");
            image = image.scaledToWidth(45);                //returns pic to original
            image = image.scaledToHeight(45);               //(not holding cheese)
            setPixmap(image);
        }

      }
}
void Jerry::gameover()
{
    QFont* f = new QFont;
    f->setPointSize(80);
    f->setBold(true);
    jerryLostOnScreen.setPlainText("GAME OVER");
    jerryLostOnScreen.setTextWidth(580);
    jerryLostOnScreen.setDefaultTextColor(QColor(Qt::red));
    jerryLostOnScreen.setX(50);
    jerryLostOnScreen.setY(450);
    jerryLostOnScreen.setFont(*f);
    jerryLostOnScreen.adjustSize();
    scene()->addItem(&jerryLostOnScreen);                       //displays text of game over
    scene()->removeItem(Tom);                                   //and removes tom object from screen

    QImage losingpic("tomcaught.png");
    QGraphicsPixmapItem* image = new QGraphicsPixmapItem(QPixmap::fromImage(losingpic));
    image->setScale(0.17);
    image->setPos(135,135);                                     //adds gameover pic
    scene()->addItem(image);

    QSound::play("gameover.wav");
}
void Jerry::victory()
{
    QFont* f = new QFont;
    f->setPointSize(90);
    f->setBold(true);
    jerryWonOnScreen.setPlainText("VICTORY");
    jerryWonOnScreen.setTextWidth(600);
    jerryWonOnScreen.setDefaultTextColor(QColor(Qt::blue));
    jerryWonOnScreen.setX(120);
    jerryWonOnScreen.setY(350);
    jerryWonOnScreen.setFont(*f);
    jerryWonOnScreen.adjustSize();
    scene()->addItem(&jerryWonOnScreen);                          //displays text of victory
    scene()->removeItem(Tom);                                     //and removes tom object from screen

    QImage losingpic("victorypic.png");
    QGraphicsPixmapItem* image = new QGraphicsPixmapItem(QPixmap::fromImage(losingpic));
    image->setScale(0.17);
    image->setPos(300,135);
    scene()->addItem(image);                                      //adds victory pic

    QSound::play("win.wav");
}

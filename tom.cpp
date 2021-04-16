#include "tom.h"

tom::tom(int d[13][13])
{
 int initialRow;
 int initialColumn;
    for (int i = 0; i < 13; i++)
        {
        for (int j = 0; j < 13; j++)
            data[i][j] = d[i][j];
         }
            //random initial position
            do
            {
            initialRow = arc4random()%7+6;
            initialColumn = arc4random()%7+6;
            }
            while(data[initialRow][initialColumn]==-1);


    QPixmap image("/Users/layla/desktop/tom.png");
    image= image.scaledToWidth(55);
    image = image.scaledToHeight(55);
    setPixmap(image);
    setPos(50 + 50 * initialRow, 50 + 50 * initialColumn);
    row = initialRow;
    column = initialColumn;



}

void tom::chase()
{
    int randomdirection;
    randomdirection = arc4random()%4;
    if (randomdirection == 0 && data[row - 1][column] != -1)
    {
        row--;
    }
    else if (randomdirection == 1 && data[row + 1][column] != -1)
    {
        row++;
    }
    else if (randomdirection == 2 && data[row][column + 1] != -1)
    {
        column++;
        QPixmap image("/Users/layla/desktop/tom.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);
        QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
        setPixmap(reflectedimage);
    }
    else if (randomdirection == 3 && data[row][column - 1] != -1)
    {
        column--;
        QPixmap image("/Users/layla/desktop/tom.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);
        setPixmap(image);
    }
    setPos(50 + 50 * column, 50 + 50 * row);
}

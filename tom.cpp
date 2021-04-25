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
    initialRow = 11;
    initialColumn = 6;


    QPixmap image("tom.png");
    image= image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);
    setPos(50 + 50 * initialRow, 50 + 50 * initialColumn);
    row = initialRow;
    column = initialColumn;
}

void tom::chase()
{
    int randomdirection;
    randomdirection = rand()%4;
    if (randomdirection == 0 && data[row - 1][column] != -1 && data[row - 1][column] != 53)
    {
        row--;
    }
    else if (randomdirection == 1 && data[row + 1][column] != -1 && data[row + 1][column] != 24)
    {
        row++;
    }
    else if (randomdirection == 2 && data[row][column + 1] != -1 && data[row][column + 1] != 36)
    {
        column++;
        QPixmap image("tom.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);
        QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
        setPixmap(reflectedimage);
    }
    else if (randomdirection == 3 && data[row][column - 1] != -1 && data[row][column - 1] != 40)
    {
        column--;
        QPixmap image("tom.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);
        setPixmap(image);
    }
    setPos(50 + 50 * column, 50 + 50 * row);
}

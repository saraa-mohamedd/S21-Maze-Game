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
    initialColumn = 6;                                  //copying board data into d[][], and initializing row and column

    QPixmap image("tom.png");
    image= image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);                                   //setting picture of tom
    setPos(50 + 50 * initialRow, 50 + 50 * initialColumn);
    row = initialRow;
    column = initialColumn;

    for (int i = 0; i < 76; i++)
        {
            for (int j = 0; j < 76; j++)
            {
                adjm[i][j] = 0;
            }
        }

     for (int i = 0; i < 13; i++)
     {
         for (int j = 0; j < 13; j++)
         {
             int node = d[i][j];
             if (node != -1)
             {
                 if (i != 0 && d[i - 1][j] != -1)
                 {
                     adjm[node][d[i - 1][j]] = 1;
                 }
                 if (j != 13 && d[i][j + 1] != -1)
                 {
                     adjm[node][d[i][j + 1]] = 1;
                 }
                 if (i != 13 && d[i + 1][j] != -1)
                 {
                     adjm[node][d[i + 1][j]] = 1;
                 }
                 if (j != 0 && d[i][j-1] != -1)
                 {
                     adjm[node][d[i][j-1]] = 1;
                 }
             }
         }
     }


}

void tom::chase()
{
    int randomdirection;
    randomdirection = rand()%4;                         //generating random number between 0 and 3 (inclusive)
                                                        //and changing direction according to number generated
    // where jerry is rn - row, column
    // where tom is rn - row, column
    // int tomnode = data[row][column];

    // na5odhom bel node number

    // sends to dijkstra the two locations
    // takes from dijstra the shortest path


    // takes that shortest path and sends it to function

    // that function moves tom along the path


    /*
    if (randomdirection == 0 && data[row - 1][column] != -1 && data[row - 1][column] != 52)
    {
        row--;
    }
    else if (randomdirection == 1 && data[row + 1][column] != -1 && data[row + 1][column] != 23)
    {
        row++;
    }
    else if (randomdirection == 2 && data[row][column + 1] != -1 && data[row][column + 1] != 35)
    {
        column++;
        QPixmap image("tom.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);               //flipping image with direction change
        QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
        setPixmap(reflectedimage);
    }
    else if (randomdirection == 3 && data[row][column - 1] != -1 && data[row][column - 1] != 39)
    {
        column--;
        QPixmap image("tom.png");
        image = image.scaledToWidth(55);
        image = image.scaledToHeight(55);
        setPixmap(image);
    }                                                   //numbers 53, 24, 36, and 40 chosen according to board
                                                        //data to not allow tom to enter home

    setPos(50 + 50 * column, 50 + 50 * row);            //setting position accordingly

    */
}

// (3 10 14 15 16)

// node tom, row, column
// nextnode popped

// data[row-1][column] == nextnode
    // row--;
// data[row+1][column] == nextnode
    //row++
// setPos(50 + 50 * column, 50 + 50 * row);





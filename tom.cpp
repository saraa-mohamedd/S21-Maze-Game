#include "tom.h"

tom::tom(int d[13][13],Jerry *jry)
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
    j = jry;

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
            if (node != -1 && node != 23 && node != 35 && node != 39 && node != 52)
            {
                if (i != 0 && d[i-1][j] != -1 && d[i-1][j] != 23 && d[i-1][j] != 35 && d[i-1][j] != 39 && d[i-1][j] != 52)
                {
                    adjm[node][d[i - 1][j]] = 1;
                }
                if (j != 13 && d[i][j+1] != -1 && d[i][j+1] != 23 && d[i][j+1] != 35 && d[i][j+1] != 39 && d[i][j+1] != 52)
                {
                    adjm[node][d[i][j + 1]] = 1;
                }
                if (i != 13 && d[i+1][j] != -1 && d[i+1][j] != 23 && d[i+1][j] != 35 && d[i+1][j] != 39 && d[i+1][j] != 52)
                {
                    adjm[node][d[i + 1][j]] = 1;
                }
                if (j != 0 && d[i][j-1] != -1 && d[i][j-1] != 23 && d[i][j-1] != 35 && d[i][j-1] != 39 && d[i][j-1] != 52)
                {
                    adjm[node][d[i][j-1]] = 1;
                }
            }
        }
    }


}

void tom::chase()
{
    jerryrow=j->getRow();
    jerrycolumn=j->getColumn();

/*    int
    randomdirection;
    randomdirection = rand()%4;     */                    //generating random number between 0 and 3 (inclusive)
                                               //and changing direction according to number generated
    // where jerry is rn - row, column
    // where tom is rn - row, column  
    jerrynode=data[jerryrow][jerrycolumn];
    tomnode=data[row][column];
    // int tomnode = data[row][column];

    // na5odhom bel node number
     // sends to dijkstra the two locations
    Dijkstra(adjm, tomnode,jerrynode);

    // takes from dikjstra the shortest path


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

vector<int> Dijkstra(int Graph[COUNT][COUNT], int tnode,int jnode)
{
    int temp[COUNT][COUNT];
    for (int i = 0; i < COUNT; i++)
    {
        for (int j = 0; j < COUNT; j++)
        {
            if (Graph[i][j] == 0)
                temp[i][j] = INFINITE;
            else
                temp[i][j] = Graph[i][j];
        }
    }
    bool visited[COUNT];
    int previous[COUNT];
    float cost[COUNT];
    // 1st Row:
    for (int i = 0; i < COUNT; i++)
    {
        if (i == tnode)
        {
            previous[i] = -1;
            cost[i] = 0;
            visited[i] = true;
        }
        else
        {
            previous[i] = tnode;
            cost[i] = temp[tnode][i];
            visited[i] = false;
        }
    }
    // All Rows:
    int count = 1;
    while (count < COUNT)
    {
        // Determine which vertex to visit.
        int minimum = INFINITE, visitedVertex;
        for (int i = 0; i < COUNT; i++)
        {
            if (visited[i] == false && cost[i] < minimum)
            {
                minimum = cost[i];
                visitedVertex = i;
            }
        }
        // Visit the vertex.
        visited[visitedVertex] = true;

        // Check whether there are shorter paths.
        for (int i = 0; i < COUNT; i++)
        {
            if (visited[i] == false)
            {
                if ((cost[visitedVertex] + temp[visitedVertex][i]) < cost[i])
                {
                    previous[i] = visitedVertex;
                    cost[i] = (cost[visitedVertex] + temp[visitedVertex][i]);
                }
            }
        }
        count++;
    }
    // Extract the paths.
    vector<vector<int>> paths;
    paths.resize(COUNT);
    int j;
    for (int i = 0; i < COUNT; i++)
    {
        paths[i].push_back(i);
        if (i != tnode)
        {
            j = i;
            do
            {
                j = previous[j];
                paths[i].insert(paths[i].begin(), j);
            } while (j != tnode);
        }
    }
    return paths[jnode];
}


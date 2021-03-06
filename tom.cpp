#include "tom.h"

tom::tom(int d[13][13], Jerry* jry)
{
    for (int i = 0; i < 13; i++)
    {
        for (int j = 0; j < 13; j++)
        data[i][j] = d[i][j];
    }
    int initialRow = 11;
    int initialColumn = 6;                                  //copying board data into d[][], and initializing row and column
    setPos(50 + 28 * initialRow, 50 + 90 * initialColumn);
    j1 = jry;

    QPixmap image("tom.png");
    image= image.scaledToWidth(50);
    image = image.scaledToHeight(50);
    setPixmap(image);                                   //setting picture of tom
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
        }                                                               // making adjacency matrix, making doors of home
                                                                        // inaccessible to tom (from both row & column)
    }


}

void tom::chase()
{
    jerryrow=j1->getRow();
    jerrycolumn=j1->getColumn();

    jerrynode=data[jerryrow][jerrycolumn];
    tomnode=data[row][column];

    if (jerrynode != 27 && jerrynode != 28 && jerrynode != 29 && jerrynode != 36 && jerrynode != 37 && jerrynode != 38 && jerrynode != 44 && jerrynode != 45 && jerrynode != 46)
    {
        // checks that the location jerry is in is not inside home, if inside home, tom does not move. otherwise,
        // sends to dijkstra the two locations
        vector<int> path = Dijkstra(adjm, tomnode, jerrynode);

        if (path.size() != 1)
        {
            int motion = path.at(1); //take the first next location in path to move to


            //find out which direction tom should move to reach this location
            if (data[row - 1][column] == motion && data[row - 1][column] != -1 && data[row - 1][column] != 52)
            {
                row--;
            }
            else if (data[row + 1][column] == motion && data[row + 1][column] != -1 && data[row + 1][column] != 23)
            {
               row++;
            }
            else if (data[row][column+1] == motion && data[row][column+1] != -1 && data[row][column+1] != 35)
            {
                column++;
                QPixmap image("tom.png");
                image = image.scaledToWidth(55);
                image = image.scaledToHeight(55);               //flipping image with direction change
                QPixmap reflectedimage = image.transformed(QTransform().scale(-1, 1));
                setPixmap(reflectedimage);
            }
            else if (data[row][column-1] == motion && data[row][column-1] != -1 && data[row][column-1] != 39)
            {
                column--;
                QPixmap image("tom.png");
                image = image.scaledToWidth(55);
                image = image.scaledToHeight(55);
                setPixmap(image);
            }
        }
    }

    setPos(50 + 50 * column, 50 + 50 * row);

}


vector<int> tom::Dijkstra(int Graph[COUNT][COUNT], int tnode,int jnode)
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


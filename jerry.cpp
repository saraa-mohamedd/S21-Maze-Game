#include "jerry.h"

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

}


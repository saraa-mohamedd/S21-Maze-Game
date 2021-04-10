#include "cheese.h"

Cheese::Cheese(int initialRow, int initialColumn)
{
QPixmap image("");
image = image.scaledToWidth(50);
image = image.scaledToHeight(50);
setPixmap(image);
setPos(50 + 50 * initialColumn, 50 + 50 * initialRow);
}
void Cheese::Adjustposition(int row, int column)
{
 setPos(50 + 50 * column, 50 + 50 * row);
}

#include "pellets.h"

Pellets::Pellets(int initialRow, int initialColumn)
{
QPixmap image("");
image = image.scaledToWidth(50);
image = image.scaledToHeight(50);
setPixmap(image);
setPos(50 + 50 * initialColumn, 50 + 50 * initialRow);
}

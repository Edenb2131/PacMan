#include "Creature.h"

Creature::Creature()
{
    x = rand() % 70 + 1;
    y = rand() % 20 + 1;
    shouldUpdate = 0;
    hoverAbove = ' ';
    direction = 's';
}

Creature::Creature(int x, int y, int shouldUpdate)
{
    this->x = x;
    this->y = y;
    this->shouldUpdate = shouldUpdate;
    hoverAbove = '.';
    direction = 's';
}

Creature::~Creature()
{
}


void Creature::setX(int x)
{
    this->x = x;
}

void Creature::setY(int y)
{
    this->y = y;
}

void Creature::setShouldUpdate(int shouldUpdate)
{
    this->shouldUpdate = shouldUpdate;
}

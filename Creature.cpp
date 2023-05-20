#include "Creature.h"
#include "Game.h"

using namespace std;

Creature::Creature(int moveFrequency) : moveFrequency(moveFrequency)
{
    x = rand() % 70 + 1;
    y = rand() % 20 + 1;
    shouldUpdate = moveFrequency;
    hoverAbove = ' ';
    direction = 's';
}

Creature::Creature(int x, int y, int moveFrequency): moveFrequency(moveFrequency)
{
    this->x = x;
    this->y = y;
    this->shouldUpdate = moveFrequency;
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

void Creature::move(Board* board, Cell pacmenPosition) {
    if (getShouldUpdate() == 0) {
        int prev_x = x;
        int prev_y = y;

        //TODO: change to use constants.
        if (hoverAbove == ' ' || hoverAbove == '.' || hoverAbove == '#') {
            board->setCell(prev_x, prev_y, hoverAbove);
            Game::gotoxy(prev_x, prev_y);
            cout << hoverAbove << endl;
        }

        UpdatePosition(board, pacmenPosition);

        hoverAbove = board->getCell(x, y);
        board->setCell(x, y, GetCreatureChar());
        Game::gotoxy(x, y);
        cout << GetCreatureChar() << endl;

        setShouldUpdate(moveFrequency);
    }
    else {
        setShouldUpdate(getShouldUpdate() - 1);
    }

}
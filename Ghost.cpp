#include "Ghost.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
using namespace std;


Ghost::Ghost(int x, int y) : Creature(1) {
    initial_x_pos = x;
    initial_y_pos = y;
    this->x = x;
    this->y = y;
    direction = DOWN_LOWER_CASE;
    hoverAbove = BREADCRUMB;
}

void Ghost::UpdatePosition(Board* board) {
    if (direction == DOWN_LOWER_CASE && y < HEIGHT-3 && y >= 1) {
        y++;
    }
    else if (direction == DOWN_LOWER_CASE && y == HEIGHT - 3) {
        direction = UP_LOWER_CASE;
        y--;
    }
    else if (direction == UP_LOWER_CASE && y == 1) {
        direction = DOWN_LOWER_CASE;
        y++;
    }
    else if (direction == UP_LOWER_CASE && y < HEIGHT - 3 && y >= 1) {
        direction = UP_LOWER_CASE;
        y--;
    }
}

void Ghost::moveToStartingPosition(Board* board) {
    board->setCell(x, y, hoverAbove);
    x = initial_x_pos;
    y = initial_y_pos;
    board->setCell(initial_x_pos, initial_y_pos, GHOST_CHAR);
}
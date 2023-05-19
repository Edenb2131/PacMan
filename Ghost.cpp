#include "Ghost.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
using namespace std;


Ghost::Ghost(int x, int y, int difficulty) : Creature(1) {
    initial_x_pos = x;
    initial_y_pos = y;
    this->x = x;
    this->y = y;
    direction = DOWN_LOWER_CASE;
    hoverAbove = BREADCRUMB;
    this->difficulty = difficulty;
}

bool IsNextMoveFree(const Board* board, const Cell& position, char direction) {
    Cell nextMove = position;
    if (direction == DOWN_LOWER_CASE) {
        nextMove.setY(nextMove.getY() + 1);
    }
    if (direction == UP_LOWER_CASE) {
        nextMove.setY(nextMove.getY() - 1);
    }
    if (direction == LEFT_LOWER_CASE) {
        nextMove.setX(nextMove.getX() - 1);
    }
    if (direction == RIGHT_LOWER_CASE) {
        nextMove.setX(nextMove.getX() + 1);
    }
    return board->getCell(nextMove.getX(), nextMove.getY()) != '#';
}

char Ghost::ChoosePosition(Board* board) {
    if (difficulty == 1 || true) {  // Move randomly when hitting a wall.
        while (!IsNextMoveFree(board, Cell(x, y), direction)) {
            const static char moves[4] = { DOWN_LOWER_CASE, UP_LOWER_CASE,  LEFT_LOWER_CASE, RIGHT_LOWER_CASE };
            direction = moves[rand() % 4];
        }
    }
    // TODO: implement other difficulties.
    return direction;
}


void Ghost::UpdatePosition(Board* board) {
    ChoosePosition(board);
    if (direction == DOWN_LOWER_CASE) {
        y++;
    }
    else if (direction == UP_LOWER_CASE) {
        y--;
    }
    else if (direction == LEFT_LOWER_CASE) {
        x--;
    }
    else if (direction == RIGHT_LOWER_CASE) {
        x++;
    }
}

void Ghost::moveToStartingPosition(Board* board) {
    board->setCell(x, y, hoverAbove);
    x = initial_x_pos;
    y = initial_y_pos;
    board->setCell(initial_x_pos, initial_y_pos, GHOST_CHAR);
}
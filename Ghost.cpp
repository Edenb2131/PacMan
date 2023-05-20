#include "Ghost.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
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

char BFS(const Cell& source, const Cell& target, const Board* board) {
    queue<pair<Cell, char>> q;
    unordered_set<std::string> seenCells;

    pair<Cell, char> curr = pair<Cell,char>(source, ' ');

    while (!curr.first.Equals(target)) {
        auto up = curr; up.first.setY(up.first.getY() - 1);
        if (up.second == ' ') up.second = UP_LOWER_CASE;

        auto down = curr; down.first.setY(down.first.getY() + 1);
        if (down.second == ' ') down.second = DOWN_LOWER_CASE;

        auto left = curr; left.first.setX(left.first.getX() - 1);
        if (left.second == ' ') left.second = LEFT_LOWER_CASE;

        auto right = curr; right.first.setX(right.first.getX() + 1);
        if (right.second == ' ') right.second = RIGHT_LOWER_CASE;

        for (const auto& neighbor : { up, down, left,  right }) {
            if (seenCells.find((std::string)neighbor.first) != seenCells.end()) {
                continue;
            }
            if (board->getCell(neighbor.first.getX(), neighbor.first.getY()) != '#') {
                q.push(neighbor);
                seenCells.insert((std::string)neighbor.first);
            }
        }
        if (q.empty()) {
            return STAY_LOWER_CASE;
        }
        curr = q.front();
        q.pop();
    }
    return curr.second; // Returnt the direction
}

char Ghost::ChoosePosition(Board* board, Cell pacmenPosition) {
    if (difficulty == 1) {  // Move randomly when hitting a wall.
        while (!IsNextMoveFree(board, Cell(x, y), direction)) {
            const static char moves[4] = { DOWN_LOWER_CASE, UP_LOWER_CASE,  LEFT_LOWER_CASE, RIGHT_LOWER_CASE };
            direction = moves[rand() % 4];
        }
    }
    else {
        direction = BFS(Cell(x, y), pacmenPosition, board);
    }
    // TODO: implement other difficulties.
    return direction;
}


void Ghost::UpdatePosition(Board* board, Cell pacmenPosition) {
    ChoosePosition(board, pacmenPosition);
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
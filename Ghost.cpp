#include "Ghost.h"
#include "Board.h"
#include "Game.h"
#include <iostream>
#include <queue>
#include <unordered_set>
#include <utility>
using namespace std;

#define DIRECTION_COUNTS 20
#define TIME_IN_STUPID 5

Ghost::Ghost(int x, int y, int difficulty) : Creature(1), direction_counter(DIRECTION_COUNTS), is_smart(true) {
    initial_x_pos = x;
    initial_y_pos = y;
    this->x = x;
    this->y = y;
    direction = DOWN_LOWER_CASE;
    hoverAbove = EMPTY;
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

char ChooseRandomDirection(Board* board, Cell position, char direction) {
   do {
        const static char moves[4] = { DOWN_LOWER_CASE, UP_LOWER_CASE,  LEFT_LOWER_CASE, RIGHT_LOWER_CASE };
        direction = moves[rand() % 4];
   } while (!IsNextMoveFree(board, position, direction));
    return direction;
}

char Ghost::ChoosePosition(Board* board, Cell pacmenPosition) {
    direction_counter--;

    if (difficulty == 3) {
        // Move randomly when hitting a wall.
        if (direction_counter == 0 || !IsNextMoveFree(board, Cell(x, y), direction)) {
            direction = ChooseRandomDirection(board, Cell(x, y), direction);
        }
    }
    else if (difficulty == 2) {
        if (direction_counter == 0) {
            is_smart = !is_smart;
            if (!is_smart) {
                direction_counter = TIME_IN_STUPID;
            }
        }
        
        if (is_smart) {
            direction = BFS(Cell(x, y), pacmenPosition, board);
        }
        // Not smart and just moved to stupid. If blocked, then also choose randomly.
        else if (direction_counter == TIME_IN_STUPID || !IsNextMoveFree(board, Cell(x, y), direction)) {
            direction = ChooseRandomDirection(board, Cell(x, y), direction);
        }
    }
    else {
        direction = BFS(Cell(x, y), pacmenPosition, board);
    }

    if (direction_counter == 0) {
        direction_counter = DIRECTION_COUNTS;
    }

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

    if (hoverAbove == EMPTY || hoverAbove == BREADCRUMB || hoverAbove == WALL) {
        board->setCell(x, y, hoverAbove);
        Game::gotoxy(x, y);
        cout << hoverAbove << endl;
    }
    x = initial_x_pos;
    y = initial_y_pos;
    board->setCell(initial_x_pos, initial_y_pos, GHOST_CHAR);
}
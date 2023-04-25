#include "Ghost.h"
#include "Board.h"

#include <iostream>
using namespace std;


Ghost::Ghost(int x, int y) {
    move_speed = 1;
    x_pos = x;
    y_pos = y;
    direction = 'x';
    hoverAbove = '.';
    shouldUpdate = true;
}

void Ghost::move(Board& board) {
    if (shouldUpdate) {
        int prev_x = x_pos;
        int prev_y = y_pos;
        board.setCell(prev_x, prev_y, hoverAbove);
        Game::gotoxy(prev_x, prev_y);
        cout << hoverAbove << endl;

        updateXY();

        hoverAbove = board.getCell(x_pos, y_pos);
        board.setCell(x_pos, y_pos, get_ghost_char());
        Game::gotoxy(x_pos, y_pos);
        cout << get_ghost_char() << endl;
    }
    shouldUpdate = !shouldUpdate; // update ghosts alternately to make them move slower then pacman.
}

void Ghost::updateXY() {
    if (direction == DOWN_LOWER_CASE && y_pos < HEIGHT-3 && y_pos >= 1) {
        y_pos++;
    }
    else if (direction == DOWN_LOWER_CASE && y_pos == HEIGHT - 3) {
        direction = UP_LOWER_CASE;
        y_pos--;
    }
    else if (direction == UP_LOWER_CASE && y_pos == 1) {
        direction = DOWN_LOWER_CASE;
        y_pos++;
    }
    else if (direction == UP_LOWER_CASE && y_pos < HEIGHT - 3 && y_pos >= 1) {
        direction = UP_LOWER_CASE;
        y_pos--;
    }
}

void Ghost::moveToStartingPosition(int new_x, int new_y, Board& board) {
    board.setCell(x_pos, y_pos, hoverAbove);
    x_pos = new_x;
    y_pos = new_y;
    board.setCell(new_x, new_y, GHOST_CHAR);
}
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
    if (direction == 'x' && y_pos < HEIGHT-3 && y_pos >= 1) {
        y_pos++;
    }
    else if (direction == 'x' && y_pos == HEIGHT - 3) {
        direction = 'w';
        y_pos--;
    }
    else if (direction == 'w' && y_pos == 1) {
        direction = 'x';
        y_pos++;
    }
    else if (direction == 'w' && y_pos < HEIGHT - 3 && y_pos >= 1) {
        direction = 'w';
        y_pos--;
    }
}
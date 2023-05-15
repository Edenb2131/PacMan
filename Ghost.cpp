#include "Ghost.h"
#include "Board.h"

#include <iostream>
using namespace std;


Ghost::Ghost(int x, int y) : Creature() {
    move_speed = 1;
    initial_x_pos = x;
    initial_y_pos = y;
    x_pos = x;
    y_pos = y;
    direction = DOWN_LOWER_CASE;
    hoverAbove = BREADCRUMB;
    setShouldUpdate(move_speed);
}

void Ghost::move(Board* board) {
    if (getShouldUpdate() == 1) {
        int prev_x = x_pos;
        int prev_y = y_pos;
        board->setCell(prev_x, prev_y, hoverAbove);
        Game::gotoxy(prev_x, prev_y);
        cout << hoverAbove << endl;

        updateXY();

        hoverAbove = board->getCell(x_pos, y_pos);
        board->setCell(x_pos, y_pos, get_ghost_char());
        Game::gotoxy(x_pos, y_pos);
        cout << get_ghost_char() << endl;

        setShouldUpdate(0) ;
    }
    else{
        int speed = getShouldUpdate();
        setShouldUpdate(++ speed); // update ghosts alternately to make them move slower then pacman.
    }

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

void Ghost::moveToStartingPosition(Board* board) {
    board->setCell(x_pos, y_pos, hoverAbove);
    x_pos = initial_x_pos;
    y_pos = initial_y_pos;
    board->setCell(initial_x_pos, initial_y_pos, GHOST_CHAR);
}
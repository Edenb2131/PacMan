#include "Ghost.h"
#include "Board.h"

#include <iostream>
using namespace std;


Ghost::Ghost(int x, int y) {
    move_speed = 1;
    x_pos = x;
    y_pos = y;
    direction = 'x';
}

void Ghost::updateXY() {
    if (direction == 'x' && y_pos < WIDTH-1) {
        y_pos++;
    }
    else if (direction == 'x' && y_pos >= WIDTH - 1) {
        direction = 'w';
        y_pos--;
    }
    
}
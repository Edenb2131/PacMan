#include "Pacman.h"
#include <iostream>
using namespace std;


Pacman::Pacman() {
    lives = MAX_NUMBER_OF_LIVES;
    move_speed = 2;
    x_pos = 39;
    y_pos = 16;
    direction = 's';
}

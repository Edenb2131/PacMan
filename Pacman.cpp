#include "Pacman.h"
#include <iostream>
using namespace std;


Pacman::Pacman() {
    lives = MAX_NUMBER_OF_LIVES;
    x_pos = PACMAN_X_STARTING_POS;
    y_pos = PACMAN_Y_STARTING_POS;
    direction = 's';
}



#ifndef PACMAN_GAME_PACMAN_H
#define PACMAN_GAME_PACMAN_H

#include <iostream>

#define PACMAN_CHAR '@'
#define MAX_NUMBER_OF_LIVES 3
#define PACMAN_X_STARTING_POS 39
#define PACMAN_Y_STARTING_POS 16

class Pacman {
    int lives;
    int x_pos;
    int y_pos;
    char direction;

public:

    Pacman();
    char get_pacman_char() const { return PACMAN_CHAR; }
    int get_lives() { return lives; }
    int get_x_pos() { return x_pos; }
    int get_y_pos() { return y_pos; }
    char get_direction() const { return direction; }

    void set_lives(int _lives) { this->lives = _lives; }
    void set_x_pos(int _x_pos) { this->x_pos = _x_pos; }
    void set_y_pos(int _y_pos) { this->y_pos = _y_pos; }
};


#endif //PACMAN_GAME_PACMAN_H

//
// Created by Eden Bar on 21/04/2023.
//

#ifndef PACMAN_GAME_PACMAN_H
#define PACMAN_GAME_PACMAN_H

#include <iostream>

class Pacman {

    int lives = 3;
    int move_speed = 2;
    int x_pos = 40;
    int y_pos = 12;
    char direction = 's';

public:

    Pacman();
    int get_lives() const { return lives; }
    int get_move_speed() const { return move_speed; }
    int get_x_pos() const { return x_pos; }
    int get_y_pos() const { return y_pos; }
    char get_direction() const { return direction; }


    void set_lives(int _lives) { this->lives = _lives; }
    void set_move_speed(int _move_speed) { this->move_speed = _move_speed; }
    void set_x_pos(int _x_pos) { this->x_pos = _x_pos; }
    void set_y_pos(int _y_pos) { this->y_pos = _y_pos; }


};


#endif //PACMAN_GAME_PACMAN_H

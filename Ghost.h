#ifndef PACMAN_GAME_GHOST_H
#define PACMAN_GAME_GHOST_H

#include "Board.h"
#include "Creature.h"

#define GHOST_CHAR '$'

class Ghost  : public Creature {
    int move_speed;
    int initial_x_pos;
    int initial_y_pos;
    int x_pos;
    int y_pos;
    char direction;
    char hoverAbove;
    
public:

    Ghost(int x, int y);
    char get_ghost_char() const { return GHOST_CHAR; }
    int get_move_speed() const { return move_speed; }
    int get_x_pos() { return x_pos; }
    int get_y_pos() { return y_pos; }
    char get_direction() const { return direction; }

    void set_move_speed(int _move_speed) { this->move_speed = _move_speed; }
    void set_x_pos(int _x_pos) { this->x_pos = _x_pos; }
    void set_y_pos(int _y_pos) { this->y_pos = _y_pos; }

    void move(Board* board);
    void updateXY();
    void moveToStartingPosition(Board* board);
};


#endif //PACMAN_GAME_GHOST_H

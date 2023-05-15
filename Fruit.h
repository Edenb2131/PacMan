#ifndef PACMAN_GAME_FRUIT_H
#define PACMAN_GAME_FRUIT_H

#include "Board.h"
#include "Ghost.h"
#include "Creature.h"

#include <random>

#define FRUIT_SPEED 4

class Fruit : public Creature
{
    int symbol;


public:
    
    int cycle_time = 10;

    Fruit();
    Fruit(int x, int y, int speed);
    ~Fruit();
    int get_symbol() {return symbol;}
    char get_symbol_as_char();

	bool moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board);
    void moveToStartingPosition(Board* board);
    void move(Board* board);
    void updateXY(Board* board);
};

#endif //PACMAN_GAME_FRUIT_H
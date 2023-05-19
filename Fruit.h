#pragma once

#include "Creature.h"
#include "Board.h"

#include <random>

#define FRUIT_SPEED 4

class Fruit : public Creature
{
    int fruitValue;


public:
    
    int cycle_time = 10;

    Fruit();
    Fruit(int x, int y, int speed);
    ~Fruit();
    int get_fruit_value() {return fruitValue;}
    char get_fruit_value_as_char();

	bool moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board);
    void moveToStartingPosition(Board* board);
    void move(Board* board);
    void updateXY(Board* board);
    void disappear(Board* board);
};
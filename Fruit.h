#pragma once

#include "Creature.h"
#include "Board.h"

#include <random>

#define FRUIT_SPEED 4

class Fruit : public Creature
{
protected:
    int fruitValue;
    int cycle_time = 10;


    virtual void UpdatePosition(Board* board);
    virtual char GetCreatureChar();
    
public:
    

    void ResetFruit();

    Fruit();
    Fruit(int x, int y, int speed);
    ~Fruit();
    int get_fruit_value() {return fruitValue;}
    
    void moveToStartingPosition(Board* board);
    
    void disappear(Board* board);
};
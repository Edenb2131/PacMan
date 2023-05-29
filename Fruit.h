#pragma once

#include "Creature.h"
#include "Board.h"

#include <random>

#define FRUIT_SPEED 4
#define FRUIT_CYCLE_TIME 10

class Fruit : public Creature
{
protected:
    int fruitValue;
    int cycle_time = 10;


    virtual void UpdatePosition(Board* board, Cell pacmenPosition) override;
    virtual char GetCreatureChar() override;
    
public:
    

    void ResetFruit(const Board* board);

    Fruit(const Board* board);
    Fruit(int x, int y, int speed);
    ~Fruit();
    int get_fruit_value() {return fruitValue;}
    
    void moveToStartingPosition(Board* board);
    
    void disappear(Board* board);
};
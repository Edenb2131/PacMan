#ifndef PACMAN_GAME_GHOST_H
#define PACMAN_GAME_GHOST_H

#include "Board.h"
#include "Creature.h"

#define GHOST_CHAR '$'

class Ghost  : public Creature {
protected:
    int initial_x_pos;
    int initial_y_pos;
    int difficulty;
    int direction_counter;
    bool is_smart;
    
    char ChoosePosition(Board* board, Cell pacmenPosition);

    virtual void UpdatePosition(Board* board, Cell pacmenPosition) override;
    virtual char GetCreatureChar() override { return GHOST_CHAR; }

public:

    Ghost(int x, int y, int difficulty);

    void moveToStartingPosition(Board* board);
};


#endif //PACMAN_GAME_GHOST_H

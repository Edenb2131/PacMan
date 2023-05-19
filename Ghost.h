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
    
    char ChoosePosition(Board* board);

    virtual void UpdatePosition(Board* board);
    virtual char GetCreatureChar() { return GHOST_CHAR; }

public:

    Ghost(int x, int y, int difficulty);

    // TODO: move to ghost manager
    void moveToStartingPosition(Board* board);
};


#endif //PACMAN_GAME_GHOST_H

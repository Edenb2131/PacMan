#pragma once

#include <array>
#include "Ghost.h"


#define GHOST_1_X_STARTING_POS 11
#define GHOST_1_Y_STARTING_POS 1
#define GHOST_2_X_STARTING_POS 68
#define GHOST_2_Y_STARTING_POS 1
#define NUMBER_OF_GHOSTS 2

class GhostManager
{
	std::array<Ghost*, NUMBER_OF_GHOSTS> ghosts;

public:
	GhostManager();
	~GhostManager();

	bool moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board);
	void moveGhostsToStartingPosition(Board* board);
};

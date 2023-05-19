#pragma once

#include <array>
#include "Ghost.h"
#include "Fruit.h"
#include "Cell.h"
#include "Board.h"

#define GHOST_1_X_STARTING_POS 11
#define GHOST_1_Y_STARTING_POS 1
#define GHOST_2_X_STARTING_POS 68
#define GHOST_2_Y_STARTING_POS 1
#define NUMBER_OF_GHOSTS 2

class CreatureManagar
{
private:
	std::vector<Ghost*> ghosts;
	int prev_x_fruit, prev_y_fruit;
	Fruit* fruit;

public:
	CreatureManagar(std::vector<Cell>& cellsOfGhosts);
	~CreatureManagar();

	bool moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board, int& addedFruitScore, bool& didCollideWithFruit);
	void moveCreatureToStartingPosition(Board* board);
};

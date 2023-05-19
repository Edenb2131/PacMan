#include "CreatureManagar.h"

CreatureManagar::CreatureManagar(std::vector<Cell>& cellsOfGhosts) {
	for (int i = 0; i < cellsOfGhosts.size(); i++) {
		Ghost* newGhost = new Ghost(cellsOfGhosts[i].getX(), cellsOfGhosts[i].getY());
		ghosts.push_back(newGhost);
	}
	fruit = new Fruit();
}

CreatureManagar::~CreatureManagar() {
	for (int i = 0; i < ghosts.size(); i++)
		delete(ghosts[i]);
}

// check collision after moving the ghosts.
bool CreatureManagar::moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board, int& addedFruitScore, bool& didCollideWithFruit) { 
	prev_x_fruit = fruit->getX(), prev_y_fruit = fruit->getY();
	// Handle Fruit
	didCollideWithFruit = fruit->moveAndCheckCollision(prev_pacman_x_pos, prev_pacman_y_pos, curr_pacman_x_pos, curr_pacman_y_pos, board);
	if (didCollideWithFruit) {
		addedFruitScore = fruit->get_fruit_value();
		fruit->disappear(board);
		delete fruit;
		fruit = new Fruit();
	}

	// Handle a cycle time for a fruit
	if (fruit->cycle_time == 0) {

		// Make sure we impement the rellevent char on the board
		char FruitCell = board->getCell(prev_x_fruit, prev_y_fruit);
		fruit->disappear(board);

		// Make a new fruit after sometime passed
		delete fruit;
		fruit = new Fruit();
	}

	for (Ghost* ghost : ghosts) {
		int prev_ghost_x_pos = ghost->get_x_pos();
		int prev_ghost_y_pos = ghost->get_y_pos();
		ghost->move(board);
		int curr_ghost_x_pos = ghost->get_x_pos();
		int curr_ghost_y_pos = ghost->get_y_pos();

		if (curr_ghost_x_pos == curr_pacman_x_pos && curr_ghost_y_pos == curr_pacman_y_pos)
			return true;
		else if (prev_ghost_x_pos == curr_pacman_x_pos && curr_ghost_x_pos == prev_pacman_x_pos && 
				 prev_ghost_y_pos == curr_pacman_y_pos && curr_ghost_y_pos == prev_pacman_y_pos)
			return true;
	}
	return false;
}

void CreatureManagar::moveCreatureToStartingPosition(Board* board) {
	for (Ghost* ghost : ghosts) {
		ghost->moveToStartingPosition(board);
	}
}
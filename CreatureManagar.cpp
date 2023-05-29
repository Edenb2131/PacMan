#include "CreatureManagar.h"

CreatureManagar::CreatureManagar(std::vector<Cell>& cellsOfGhosts, int difficulty, int amountOfFruits) {
	for (int i = 0; i < cellsOfGhosts.size(); i++) {
		Ghost* newGhost = new Ghost(cellsOfGhosts[i].getX(), cellsOfGhosts[i].getY(), difficulty);
		ghosts.push_back(newGhost);
	}
	for (int i = 0; i < amountOfFruits; i++) {
		fruits.push_back(new Fruit());
	}
}

CreatureManagar::~CreatureManagar() {
	for (int i = 0; i < ghosts.size(); i++)
		delete(ghosts[i]);
}

// A struct to keep track of all ghosts positions before and after moving.
// This is an internal implementation requirement of `moveAndCheckCollision`,
// and therefore kept in the .cpp file.
struct GostPositions {
	Cell prev;
	Cell curr;

	GostPositions(Cell prev, Cell  curr): prev(prev), curr(curr){}
};

// check collision after moving the ghosts.
bool CreatureManagar::moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board, int& addedFruitScore, bool& didCollideWithFruit) { 
	Cell pacmen_curr = Cell(curr_pacman_x_pos, curr_pacman_y_pos);
	Cell pacmen_prev = Cell(prev_pacman_x_pos, prev_pacman_y_pos);
	
	addedFruitScore = 0;
	// Handle ghosts.
	vector<GostPositions> ghosts_positions;
	for (Ghost* ghost : ghosts) {
		Cell ghost_prev = ghost->getPosition();
		ghost->move(board, pacmen_curr);
		Cell ghost_curr = ghost->getPosition();

		if (DidCollide(ghost_prev, ghost_curr, pacmen_prev, pacmen_curr)) {
			return true;
		}
		ghosts_positions.push_back(GostPositions(ghost_prev, ghost_curr));
	}


	// Handle Fruits.
	for (Fruit* fruit : fruits) {
		Cell fruit_prev = fruit->getPosition();
		fruit->move(board, pacmen_curr);
		Cell fruit_curr = fruit->getPosition();
		bool didCollideWithCurrentFruit = DidCollide(fruit_prev, fruit_curr, pacmen_prev, pacmen_curr);
		if (didCollideWithCurrentFruit) {
			didCollideWithFruit = true;
			addedFruitScore += fruit->get_fruit_value();
			fruit->disappear(board);
			fruit->ResetFruit();
		}
		for (const GostPositions& ghost : ghosts_positions) {
			bool didGhostCollideWithCurrentFruit = DidCollide(fruit_prev, fruit_curr, ghost.prev, ghost.curr);
			if (didGhostCollideWithCurrentFruit) {
				fruit->disappear(board);
				fruit->ResetFruit();
				break;
			}
		}
	}

	return false;
}

bool CreatureManagar::DidCollide(Cell creature_prev, Cell creature_curr, Cell pacmen_prev, Cell pacmen_curr) {
	if (creature_curr.Equals(pacmen_curr)) {
		return true;
	}
	if (creature_curr.Equals(pacmen_prev) && creature_prev.Equals(pacmen_curr)) {
		return true;
	}
	return false;
}

void CreatureManagar::moveCreatureToStartingPosition(Board* board) {
	for (Ghost* ghost : ghosts) {
		ghost->moveToStartingPosition(board);
	}
}
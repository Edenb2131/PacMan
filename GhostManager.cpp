#include "GhostManager.h"

GhostManager::GhostManager() {
	ghosts[0] = new Ghost(GHOST_1_X_STARTING_POS, GHOST_1_Y_STARTING_POS);
	ghosts[1] = new Ghost(GHOST_2_X_STARTING_POS, GHOST_2_Y_STARTING_POS);
}

GhostManager::~GhostManager() {
	for (int i = 0; i < NUMBER_OF_GHOSTS; i++)
		delete(ghosts[i]);
}

// check collision after moving the ghosts.
bool GhostManager::moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board) {

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

void GhostManager::moveGhostsToStartingPosition(Board* board) {
	for (Ghost* ghost : ghosts) {
		ghost->moveToStartingPosition(board);
	}
}
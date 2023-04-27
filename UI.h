#ifndef PACMAN_GAME_UI_H
#define PACMAN_GAME_UI_H

#include <iostream>
#include "Game.h"

class UI
{
public:
	static int get_players_choice();
	static void print_menu();
	static void print_InstAndKeys();
};

#endif //PACMAN_GAME_UI_H


#ifndef PACMAN_GAME_UI_H
#define PACMAN_GAME_UI_H

#include <iostream>

class UI
{
public:
	static int get_players_choice();
	static int get_players_choice_for_diff();
	static int get_players_choice_for_maps();
	static std::string get_map_name();
	static void print_menu();
	static void print_difficulty_menu();
	static void print_InstAndKeys();
	static void print_game_maps_choice();
};

#endif //PACMAN_GAME_UI_H


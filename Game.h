//
// Created by Eden Bar on 21/04/2023.
//

#ifndef PACMAN_GAME_GAME_H
#define PACMAN_GAME_GAME_H

#include <iostream>

class Game {

    int score = 0;
    // int max_score = 0;

public:

    Game();
    void print_menu();
    void start();
    static int get_players_choice();
    static void print_InstAndKeys();

};


#endif //PACMAN_GAME_GAME_H

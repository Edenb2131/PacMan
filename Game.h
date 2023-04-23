//
// Created by Eden Bar on 21/04/2023.
//

#ifndef PACMAN_GAME_GAME_H
#define PACMAN_GAME_GAME_H

#include <iostream>

class Board;
#include "Board.h"
#include "Ghost.h"
#include "Pacman.h"

class Game {

    int score = 0;
    int max_score = 0;
    void play(int x, int y, char d, Board& board);
public:

    Game();
    void print_menu();
    void start();
    void change_max_score_if_needed(int _max_score);
    void player_lost_msg();
    static int get_players_choice();
    static void print_InstAndKeys();
    static void gotoxy(int x, int y);
};

                        

#endif //PACMAN_GAME_GAME_H

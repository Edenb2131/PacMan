#ifndef PACMAN_GAME_GAME_H
#define PACMAN_GAME_GAME_H

#include <iostream>

class Ghost;
class Board;
class Pacman;
#include "Board.h"
#include "Pacman.h"

#define START 1
#define INSTRUCTIONS 8
#define EXIT 9
#define UP_LOWER_CASE 'w'
#define UP_UPPER_CASE 'W'
#define DOWN_LOWER_CASE 'x'
#define DOWN_UPPER_CASE 'X'
#define LEFT_LOWER_CASE 'a'
#define LEFT_UPPER_CASE 'A'
#define RIGHT_LOWER_CASE 'd'
#define RIGHT_UPPER_CASE 'D'
#define STAY_LOWER_CASE 's'
#define STAY_UPPER_CASE 'S'
#define BREADCRUMB '.'
#define EMPTY ' '
#define NUMBER_OF_GHOSTS 2
#define GHOST_1_X_POS 11
#define GHOST_1_Y_POS 1
#define GHOST_2_X_POS 68
#define GHOST_2_Y_POS 1


class Game {
    int score = 0;
    int max_score = 0;
    Pacman pacman;
    Ghost* ghosts[NUMBER_OF_GHOSTS];
    void play(int x, int y, char d, Board& board);
public:

    Game();
    ~Game();
    void print_menu();
    void start();
    void change_max_score_if_needed(int _max_score);
    void player_lost_msg();
    static int get_players_choice();
    static void print_InstAndKeys();
    static void gotoxy(int x, int y);
};

                        

#endif //PACMAN_GAME_GAME_H

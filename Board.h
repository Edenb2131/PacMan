//
// Created by Eden Bar on 21/04/2023.
//
#ifndef PACMAN_GAME_BOARD_H
#define PACMAN_GAME_BOARD_H


#include <iostream>
#include <vector>
#include <string>
#include <array>

//#include "Game.h"
//#include "Ghost.h"
//#include "breadcrumbs.h"
//#include "Pacman.h"

#define WIDTH 80
#define HEIGHT 25

using std::vector;

class Board {
    vector<vector<char>> board;
    //    char board[HEIGHT][WIDTH]{};
    void print_last_row(int _lives, int _score);
public:

    Board(int _lives, int _score);
    vector<vector<char>> get_board() { return board; }
    void print(int _lives, int _score);
};


#endif //PACMAN_GAME_BOARD_H

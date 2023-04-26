#ifndef PACMAN_GAME_BOARD_H
#define PACMAN_GAME_BOARD_H


#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "Game.h"

#define WIDTH 80
#define HEIGHT 25

using std::vector;

class Board {
    vector<vector<char>> board;
    int totalNumberOfBreadcrumbs;
public:

    Board(int _lives, int _score);
    vector<vector<char>> get_board() { return board; }
    void print(int _lives, int _score);
    void update_score_board(int _score);
    void setCell(int x, int y, char ch);
    char getCell(int x, int y) const;
    void print_last_row(int _lives, int _score);
    int gettotalNumberOfBreadcrumbs() const { return totalNumberOfBreadcrumbs; }
    int countTotalNumberOfBreadcrumbs() const;
};


#endif //PACMAN_GAME_BOARD_H

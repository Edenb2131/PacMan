#ifndef PACMAN_GAME_BOARD_H
#define PACMAN_GAME_BOARD_H


#include <iostream>
#include <vector>
#include <string>
#include <array>
#include "Pacman.h"
#include "FileHandler.h"
#include "Cell.h"
#include "UI.h"

#define WIDTH 80
#define HEIGHT 25
#define BREADCRUMB '.'
#define EMPTY ' '
#define WALL '#'

class Pacman;
class FileHandler;
using std::vector;

class Board {
    vector<vector<char>> board;
    int totalNumberOfBreadcrumbs;
    vector<FileHandler> maps;
public:

    Board(int _lives, int _score, int map_choice);
    vector<vector<char>> get_board() { return board; }
    void print(int _lives, int _score);
    void update_score_board(int _score);
    void setCell(int x, int y, char ch);
    void setCellInvers(int x, int y, char ch);
    char getCell(int x, int y) const;
    void print_last_row(int _lives, int _score);
    int gettotalNumberOfBreadcrumbs() const { return totalNumberOfBreadcrumbs; }
    int countTotalNumberOfBreadcrumbs() const;
    std::vector<Cell> getGhostsStartingPosition() const;
    void getPacManStaringPostion(Pacman* pacman) ;
};


#endif //PACMAN_GAME_BOARD_H

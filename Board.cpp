#include "Board.h"
#include <iostream>
using namespace std;


Board::Board(int _lives, int _score) {

    // Making the board size of 25x80
    board.resize(HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
        board[i].resize(WIDTH);

    array<string, HEIGHT> map_sketch = {
            "################################################################################",
            "#......................................#.......................................#",
            "#...######...#######################...#...########################...######...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...######...#######################...#...########################...######...#",
            "#..............................................................................#",
            "##########...#...###################   #   ####################...#...##########",
            "         #...#............#            #             #........... #...#         ",
            "         #...##########...#                          #...##########...#         ",
            "##########...##########...#                          #...##########...##########",
            "..........................#                          #..........................",
            "##########...##########...#                          #...##########...##########",
            "         #...##########...############################...##########...#         ",
            "         #...#....................................................#...#         ",
            "##########...#...##############################################...#...##########",
            "#...................................... .......................................#",
            "#...######...#######################...#...########################...######...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...######...#######################...#...########################...######...#",
            "#..............................................................................#",
            "################################################################################",
    };


    for (int i = 0; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = map_sketch[i][j];
        }
    }
    print_last_row(_lives, _score);
}

void Board::print(int _lives, int _score) {
    for (int row = 0; row < HEIGHT - 1; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << board[row][col];
        }
        cout << endl;
    }
    print_last_row(_lives, _score);
}


void Board::print_last_row(int _lives, int _score) {

    // add "Number of lives: " and "Score: " to the last row using strings
    string lives = "Number of lives: " + to_string(_lives);
    string score = "Score: " + to_string(_score);

    // add lives to the board
    for (int i = 0; i < lives.length(); i++) {
        board[HEIGHT - 1][i] = lives[i];
    }

    // add "Score: " to the last row
    int score_start =int(WIDTH - score.length());
    for (int i = score_start; i < WIDTH; i++) {
        board[HEIGHT - 1][i - 3] = score[i - score_start];
    }

    // Making white space in last row
    for (int i = 0; i < WIDTH - score.length() - lives.length() - 3; i++) {
        board[HEIGHT - 1][lives.length() + i] = ' ';
    }

    // Printing the last row
    for (int i = 0; i < WIDTH; i++)
        cout << board[HEIGHT - 1][i];
    cout << endl;
     
}

 void Board::update_score_board(int _score) {
     // board[HEIGHT - 1][79] = '0' + _score;
     Game::gotoxy(76, 24);
     cout << _score;
 }

 void Board::setCell(int x, int y, char ch) {
     board[y][x] = ch;
 }

 char Board::getCell(int x, int y) const {
     return board[y][x];
 }

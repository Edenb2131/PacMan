//
// Created by Eden Bar on 21/04/2023.
//

#include "Board.h"
#include <iostream>
using namespace std;

Board::Board() {

    // Making the board size of 25x80
    board.resize(HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
        board[i].resize(WIDTH);

    array<string, HEIGHT> map_sketch = {
            "################################################################################",
            "#                                      #                                       #",
            "#   ######   #######################   #   ########################   #####    #",
            "#   #    #   #                     #   #   #                      #   #   #    #",
            "#   #    #   #                     #   #   #                      #   #   #    #",
            "#   ######   #######################   #   ########################   #####    #",
            "#                                                                              #",
            "##########   #   ###################   #   ####################   #   ##########",
            "         #   #            #            #             #            #   #         ",
            "         #   ##########   #                          #   ##########   #         ",
            "##########   ##########   #                          #   ##########   ##########",
            "                          #                          #                          ",
            "##########   ##########   #                          #   ##########   ##########",
            "         #   ##########   ############################   ##########   #         ",
            "         #   #                                                    #   #         ",
            "##########   #   ##############################################   #   ##########",
            "#                                                                              #",
            "#   ######   #######################   #   ########################   #####    #",
            "#   #    #   #                     #   #   #                      #   #   #    #",
            "#   #    #   #                     #   #   #                      #   #   #    #",
            "#   #    #   #                     #   #   #                      #   #   #    #",
            "#   ######   #######################   #   ########################   #####    #",
            "#                                                                              #",
            "################################################################################",
    };


    for (int i = 0; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = map_sketch[i][j];
        }
    }


    // add "Number of lives: " and "Score: " to the last row using strings
    string lives = "Number of lives: 3";
    string score = "Score: 0";

    // add lives to the board
    for (int i = 0; i < lives.length(); i++) {
        board[HEIGHT - 1][i] = lives[i];
    }

    // add "Score: " to the last row
    int score_start = WIDTH - score.length();
    for (int i = score_start; i < WIDTH; i++) {
        board[HEIGHT - 1][i] = score[i - score_start];
    }

    // Making white space
    for (int i = 0; i < WIDTH - score.length() - lives.length(); i++) {
        board[HEIGHT - 1][lives.length() + i] = ' ';
    }
}

void Board::print() {
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            cout << board[row][col];
        }
        cout << endl;
    }
}
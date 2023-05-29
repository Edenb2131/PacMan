#include "Board.h"
#include <iostream>
#include "Game.h"
#include<windows.h>
using namespace std;


Board::Board(int _lives, int _score, int map_choice) {

    
    if (map_choice == 1 || map_choice == 2) {
        maps.resize(3);
        for (int i = 0; i < 3; i++) {
            maps[0].readMapFromFile(this, "pacman_a.screen");
            maps[1].readMapFromFile(this, "pacman_b.screen");
            maps[2].readMapFromFile(this, "pacman_c.screen");
        }
        if (map_choice == 1) { // means we going continuesly throw levels
            SetMap(0);
        }
        else if (map_choice == 2) {// means we are picking a random level
            int random = rand() % 3;
            SetMap(random);
        }
    }
    else if(map_choice == 3) { // means the player choose a spesific map
        string map_name = UI::get_map_name();
        maps.resize(1);
        if (!FileHandler::CheckFile(map_name)) {
            cout << "\nFile does not exist. Loading file #1.\n";
            maps[0].readMapFromFile(this, "pacman_a.screen");
            Sleep(3000);
        }
        else {
            maps[0].readMapFromFile(this, map_name);
        }
        SetMap(0);
    }
    

    print_last_row(_lives, _score);
}

void Board::SetMap(int mapIndex) {
    current_map_index = mapIndex;

    // Making the board size of 25x80
    board.resize(HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
        board[i].resize(WIDTH);

    for (int i = 0; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            this->setCellInvers(i, j, maps[mapIndex].get()[i][j]);
        }
    }
    totalNumberOfBreadcrumbs = countTotalNumberOfBreadcrumbs();
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
    const int scoreSizePixels = 10;
    
    // add lives to the board
    for (int i = 0; i < lives.length(); i++) {
        board[HEIGHT - 1][i] = lives[i];
    }

    // add "Score: " to the last row
    int score_start =int(WIDTH - scoreSizePixels);
    for (int i = score_start; i < score_start + score.length(); i++) {
        board[HEIGHT - 1][i - 3] = score[i - score_start];
    }

    // Making white space in last row
    for (int i = 0; i < WIDTH - scoreSizePixels - lives.length() - 3; i++) {
        board[HEIGHT - 1][lives.length() + i] = ' ';
    }

    // Printing the last row
    for (int i = 0; i < WIDTH; i++)
        cout << board[HEIGHT - 1][i];
    cout << endl;
     
}

 void Board::update_score_board(int _score) {
     Game::gotoxy(74, HEIGHT - 1);

     cout << _score;
 }

 void Board::setCell(int x, int y, char ch) {
     board[y][x] = ch;
 }

 void Board::setCellInvers(int x, int y, char ch) {
     board[x][y] = ch;
 }

 char Board::getCell(int x, int y) const {
     if (y < 0 || y >= board.size()) {
         return WALL;
     }
     if (x < 0 || x >= board[y].size()) {
         return WALL;
     }
     return board[y][x];
 }

 int Board::countTotalNumberOfBreadcrumbs() const {
     int counter = 0;
     for (int i = 0; i < HEIGHT - 1; i++) {
         for (int j = 0; j < WIDTH; j++) {
             if (board[i][j] == BREADCRUMB) {
                 counter++;
             }
         }
     }
     return counter;
 }

 // gets the init positions of the ghosts
 vector<Cell> Board::getGhostsStartingPosition() const {
     vector<Cell> ghostsLocations;
     for (int i = 0; i < HEIGHT - 1; i++) {
         for (int j = 0; j < WIDTH; j++) {
             if (board[i][j] == GHOST_CHAR) {
                 ghostsLocations.push_back(Cell(j, i));
             }
         }
     }
     return ghostsLocations;
}

 // gets the init positions of the pacman
 void Board::getPacManStaringPostion(Pacman* pacman) 
 {
     for (int i = 0; i < HEIGHT - 1; i++) {
         for (int j = 0; j < WIDTH; j++) {
             if (board[i][j] == PACMAN_CHAR) {
                    pacman->set_x_pos(j);
                    pacman->set_y_pos(i);
                    board[i][j] = EMPTY;
                    return;
             }
         }
     }

 }

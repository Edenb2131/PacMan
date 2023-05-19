#include "Board.h"
#include <iostream>
#include "Game.h"
using namespace std;


Board::Board(int _lives, int _score, int map_choice) {

    // Making the board size of 25x80
    board.resize(HEIGHT);
    for (int i = 0; i < HEIGHT; i++)
        board[i].resize(WIDTH);

 /*   array<string, HEIGHT> map_sketch = {
            "################################################################################",
            "#..........$...........................#............................$..........#",
            "#...## ###...######### #############...#...############## #########...### ##...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...## ###...######### #############...#...############## #########...### ##...#",
            "#..............................................................................#",
            "#### #####...#...###################   #   ####################...#...##### ####",
            "#        #...#............#            #             #............#...#        #",
            "#        #...##########...#                          #...##########...#        #",
            "#### #####...##########...#                          #...##########...##### ####",
            "..........................#                          #..........................",
            "#### #####...##########...#                          #...##########...##### ####",
            "#        #...##########...############################...##########...#        #",
            "#        #...#....................................................#...#        #",
            "#### #####...#...##############################################...#...##### ####",
            "#...................................... .......................................#",
            "#...## ###...######### #############...#...############# ##########...### ##...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...#    #...#                     #...#...#                      #...#    #...#",
            "#...## ###...######### #############...#...############# ##########...### ##...#",
            "#..........$........................................................$..........#",
            "################################################################################",
    };

    for (int i = 0; i < HEIGHT - 1; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = map_sketch[i][j];
        }
    }

    */
    maps.resize(3);
    for ( int i = 0 ; i < 3; i ++){
        maps[i].did_load = 0;
    }

    if(map_choice == 1){ // means we going continuesly throw levels
        maps[0].readMapFromFile(this, "pacman_a.screen.txt");
        maps[0].did_load = 1;
        maps[1].readMapFromFile(this, "pacman_b.screen.txt");
        maps[1].did_load = 1;
        maps[2].readMapFromFile(this, "pacman_c.screen.txt");
        maps[2].did_load = 1;
    }
    else if(map_choice == 2) {// means we are picking a random level
        int random = rand() % 3;
        if (random == 0) {
            maps[0].readMapFromFile(this, "pacman_a.screen.txt");
            maps[0].did_load = 1;
        }
        else if (random == 1) {
            maps[1].readMapFromFile(this, "pacman_b.screen.txt");
            maps[1].did_load = 1;
        }
        else {
            maps[2].readMapFromFile(this, "pacman_c.screen.txt");
            maps[2].did_load = 1;
        }
    }
    else if(map_choice == 3) { // means the player choose a spesific map
        int map_number;
        UI::get_players_choice_for_maps(map_number);

        if (map_number == 1) {
            maps[0].readMapFromFile(this, "pacman_a.screen.txt");
            maps[0].did_load = 1;
        }
        else if (map_number == 2) {
            maps[1].readMapFromFile(this, "pacman_b.screen.txt");
            maps[1].did_load = 1;
        }
        else {
            maps[2].readMapFromFile(this, "pacman_c.screen.txt");
            maps[2].did_load = 1;
        }
    }
    

    print_last_row(_lives, _score);
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

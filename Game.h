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
#define SCREEN_FREEZE (char)27
#define BREADCRUMB '.'
#define EMPTY ' '
#define NUMBER_OF_GHOSTS 2
#define GHOST_1_X_STARTING_POS 11
#define GHOST_1_Y_STARTING_POS 1
#define GHOST_2_X_STARTING_POS 68
#define GHOST_2_Y_STARTING_POS 1

enum class GameStatus {
    PlayerWon,
    PlayerLost
};

class Game {
    int total_score = 0;
    Board* board;
    Pacman pacman;
    std::array<Ghost*, NUMBER_OF_GHOSTS> ghosts;
    GameStatus play(int x, int y, char d);

public:
    Game();
    ~Game();
    void start();
    void player_end_message(bool& didPlayerWin);
    static void gotoxy(int x, int y);
    bool isGamePinished(bool& didPlayerWin);
    void initLivesAndScore();
    void UpdatePositionAccordingToUser(int& x, int& y, char prev_direction, char& direction, bool& is_screen_frozen);
    bool check_if_hit_obstacle(int x, int y);
};            

#endif //PACMAN_GAME_GAME_H

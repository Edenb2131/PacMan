#ifndef PACMAN_GAME_GAME_H
#define PACMAN_GAME_GAME_H

#include <iostream>

#include "Board.h"
#include "Pacman.h"
#include "CreatureManagar.h"
class Fruit;
class Board;
class Pacman;

#define START 1
#define BEST 1
#define INSTRUCTIONS 8
#define EXIT 9
#define GOOD 2
#define NOVICE 3
#define NUMBER_Of_MAPS 3
#define COLLIDEWITHFRUIT 88
#define COLLIDEWITHGHOST 99
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

enum class GameStatus {
    PlayerWon,
    PlayerLost
};

class Game {
    int total_score = 0;
    int difficulty = -1;
    int map_choice = -1;
    Board* board;
    Pacman* pacman;
    CreatureManagar* creatureManager;
    GameStatus playOneRound(int x, int y, char d);

public:
    Game();
    ~Game();
    void start();
    void setDifficulty(int difficulty);
    void getDifficultyFromUser();
    int getDifficulty() { return difficulty;}
    std::string getDifficultyString(); 
    void player_end_message(bool& didPlayerWin);
    static void gotoxy(int x, int y);
    bool isGameFinished(bool& didPlayerWin);
    void updatePositionAccordingToUser(int& x, int& y, char prev_direction, char& direction, bool& is_screen_frozen);
    bool check_if_hit_wall(int x, int y);
};            

#endif //PACMAN_GAME_GAME_H

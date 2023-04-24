//
// Created by Eden Bar on 21/04/2023.
//

#include "Game.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

void clrscreen();                                      // prototype
bool check_if_hit_boarder(int x, int y ,Board &board); // prototype

void Game::print_menu() {
    // Present the menu
    cout << "Welcome to Pacman!" << endl;
    cout << "1. Start a new Game" << endl;
    cout << "8. Present instructions and keys" << endl;
    cout << "9. Quit" << endl;
}

Game::Game() {
    print_menu();
    int choice = get_players_choice();
    score = 0;
    while (true) {
        // Start a new game
        if (choice == 1)
            start();
        if (choice == 8)
            print_InstAndKeys();
        if (choice == 9) {
            cout << "Thanks for playing PAC-MAN!" << endl;
            exit(0);
        }
        cout << endl;

        print_menu();
        choice = get_players_choice();
    }
}

int Game::get_players_choice() {
    int choice;
    cin >> choice;

    if (choice != 1 && choice != 8 && choice != 9) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }

    return choice;
}


void Game::start() {
    // Start the game
    Pacman pacman;
    Ghost ghost_1(1, 11);
    Ghost ghost_2(1, 68);
    Board board = Board(pacman.get_lives(), score);


    // Main game loop
    while (pacman.get_lives() > 0) {

        // Get starting proporties for Pac-Man
        int pacman_x = pacman.get_x_pos();
        int pacman_y = pacman.get_y_pos();
        int lives = pacman.get_lives();

        // Get starting proporties for ghost 1
        int ghost_1_x = ghost_1.get_x_pos();
        int ghost_1_y = ghost_1.get_y_pos();
        char prev_char_1 = board.get_board()[ghost_1_x][ghost_1_y];
        board.setCell(ghost_1_x, ghost_1_y, '$');
        ghost_1.updateXY();
        //board.setCell(ghost_1_x, ghost_1_y, prev_char_1);


        // Get starting proporties for ghost 2
        int ghost_2_x = ghost_2.get_x_pos();
        int ghost_2_y = ghost_2.get_y_pos();
        char prev_char_2 = board.get_board()[ghost_2_x][ghost_2_y];
        ghost_2.updateXY();
        //board.setCell(ghost_2_x, ghost_2_y, prev_char_2);


        cin.clear(); // This is to flush the buffer
        char d = pacman.get_direction();

        clrscreen();
        board.print(pacman.get_lives(), score);

        // play 1 life
        play(pacman_x, pacman_y, d, board, ghost_1, ghost_2);
        
        // Set life for Pac-Man
        pacman.set_lives(--lives);

        // Annpuncing that life has been taking
        gotoxy(WIDTH /2 - 10 , HEIGHT - 1);
        cout << "You Lost a life " << endl;

        Sleep(2000);

        change_max_score_if_needed(score);
        score = 0; // Staring a new life \ game with score = 0
    }

    // PLayer has lost the game - showing massge and max score
    player_lost_msg();

    Sleep(2000);
    clrscreen();

}

void Game::play(int x, int y, char d, Board& board, Ghost ghost_1, Ghost ghost_2) {

    while (!check_if_hit_boarder(x, y, board)) {

        if (_kbhit())
            d = _getch();

        switch (d) {
        case 'd':
            ++x;
            break;
        case 'w':
            --y;
            break;
        case 'a':
            --x;
            break;
        case 'x':
            ++y;
            break;
        case 's':
            break;

        default:
            d = 's';
            break;
        }

        // handeling moving between right - left walls
        if (x == 0 && y == 11 && d == 'a')
            x = 79;

        if (x == 79 && y == 11 && d == 'd')
            x = 0;

        // Just to check the X and Y of the player
        Game::gotoxy(1, 26);
        cout << x << "  " << y;

        Game::gotoxy(x, y);
        char c = board.get_board()[y][x];
        cout << "@" << endl;

        Sleep(200);

        // If eat breadcrumbs then chnage the score
        if (c == '.') {
            c = ' ';
            score++;
        }
 
        Game::gotoxy(x, y);
        cout << c << endl;

        // Handle ghosts
        //Game::gotoxy(ghost_1.get_x_pos(), ghost_1.get_y_pos());
        
       // Game::gotoxy(ghost_2.get_x_pos(), ghost_2.get_y_pos());
      //  cout << "$" << endl;

        // Update the score on board
        board.update_score_board(score);

    }

}


void Game::print_InstAndKeys() {
    // Print the instructions and keys
    cout << "Instructions:" << endl;
    cout << "   Eat all the dots to win the game." << endl;
    cout << "   Use the keys to move." << endl;
    cout << "Keys:" << endl;
    cout << "   W arrow - move up" << endl;
    cout << "   X arrow - move down" << endl;
    cout << "   A arrow - move left" << endl;
    cout << "   D arrow - move right" << endl;
    cout << "   S arrow - stay" << endl;
}




// function definition -- requires windows.h
void Game::gotoxy(int x, int y)
{
    HANDLE hConsoleOutput;
    COORD dwCursorPosition;
    cout.flush();
    dwCursorPosition.X = x;
    dwCursorPosition.Y = y;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h
void clrscreen()
{
    system("cls");
}

// function that checks if we hit a wall
bool check_if_hit_boarder(int x, int y, Board &board) {
    
    // Check if hit the boarder or # sign
    if (x != 0 && y != 11 || x !=79 && y !=11) // To make sure this wont inturpt swtiching sides
        if (x == 0 || x == 79 || y == 0 || y == 24)
            return true;
    
    // Check if hit a # sign (wall)
    if (board.get_board()[y][x] == '#')
        return true;

    // Check if hit a $ sign (ghost)
    if (board.get_board()[y][x] == '$')
        return true;
    
    return false;
}


void Game::change_max_score_if_needed(int _max_score) {

    if (_max_score > max_score) {
        max_score = _max_score;
        gotoxy(76, 24);
        cout << "    ";
    }
}


void Game::player_lost_msg() {

    // Game has ended - 3 lives were done
    clrscreen();
    cout << " YOU LOST THE GAME !" << endl;
    cout << " Your max score is: " << max_score;

}
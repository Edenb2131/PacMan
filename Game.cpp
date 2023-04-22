//
// Created by Eden Bar on 21/04/2023.
//

#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;


#include "Game.h"
#include "Board.h"
#include "Ghost.h"
#include "Pacman.h"

void gotoxy(int x, int y);                             // prototype
void clrscr();                                         // prototype
bool check_if_hit_boarder(int x, int y ,Board &board); // prototype

void Game::print_menu() {
    // Present the menu
    cout << "Welcome to Pacman!" << endl;
    cout << "1. Start a new Game" << endl;
    cout << "2. Present instructions and keys" << endl;
    cout << "3. Quit" << endl;
}

Game::Game() {
    print_menu();
    int choice = get_players_choice();
   
    while (true) {
        // Start a new game
        if (choice == 1)
            start();
        if (choice == 2)
            print_InstAndKeys();
        if (choice == 3) {
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

    if (choice < 1 || choice > 3) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }

    return choice;
}


void Game::start() {
    // Start the game

    Pacman pacman;
    Board board = Board(pacman.get_lives(), 0);

    // Main game loop
    while (pacman.get_lives() > 0) {
        int x = pacman.get_x_pos();
        int y = pacman.get_y_pos();
        char d = pacman.get_direction();

        system("cls");
        board.print(pacman.get_lives(), 0);


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
                    gotoxy(WIDTH / 2 - 18, HEIGHT - 1);
                    cout << " ERORR! - hit a wrong charcter"; ///////// NNED to change //////
                    d = 's';
                    break;

            }
                
            gotoxy(x, y);
            char c = board.get_board()[y][x];
            cout << "@" << endl;

            Sleep(200);

            gotoxy(x, y);
            cout << c << endl;
            

        }

        int lives = pacman.get_lives();
        pacman.set_lives(--lives);

        gotoxy(WIDTH /2 - 10 , HEIGHT - 1);
        cout << "You Lost this life " << endl;
        Sleep(2000);
    }

    // Game has ended - 3 lives were done
    system("cls");
    cout << "                                 YOU LOST THE GAME !" << endl;

    Sleep(2000);
    system("cls");

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
void gotoxy(int x, int y)
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
void clrscr()
{
    system("cls");
}

// function that checks if we hit a wall
bool check_if_hit_boarder(int x, int y, Board &board) {
    
    // Check if hit the boarder or # sign
    if (x == 0 || x == 79 || y == 0 || y == 24)
        return true;
    
    // Check if hit a # sign
    if (board.get_board()[y][x] == '#')
        return true;
    
    return false;
}

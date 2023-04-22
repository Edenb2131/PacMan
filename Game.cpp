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

void gotoxy(int x, int y);               // prototype
void clrscr();                           // prototype
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
   // int choice = get_players_choice();
    int choice = 1;
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
    system("cls");

    Board board;
    Pacman pacman;

    board.print();
    //flushall();

    int x = pacman.get_x_pos();
    int y = pacman.get_y_pos();

    while (pacman.get_lives() > 0) {

        while (!kbhit()) {

            char d = pacman.get_direction();
            

            gotoxy(x, y);
            cout << "@" << endl;
            Sleep(100);

            gotoxy(x, y);
            cout << " " << endl;

            ++x;
            ++y;

            
            

        }
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




bool check_if_hit_boarder(int x, int y, Board &board) {
    
    // Check if hit the boarder or # sign
    if (x == 0 || x == 79 || y == 0 || y == 24)
        return true;
    
    // Check if hit a # sign
    if (board[x][y] == '#')
        return true;
    
    return false;
}
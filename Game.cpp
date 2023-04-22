//
// Created by Eden Bar on 21/04/2023.
//

#include <iostream>
using namespace std;


#include "Game.h"
#include "Board.h"
#include "Ghost.h"
#include "Pacman.h"


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
    Board board;
    board.print();
    Pacman pacman;
    while (pacman.get_lives() > 0) {
        //        pacman.move();
        //        board.print();
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





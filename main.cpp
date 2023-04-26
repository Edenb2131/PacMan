#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "Game.h"

using namespace std;

void print_menu();
static int get_players_choice();
static void print_InstAndKeys();

int main() {

    while (true) {
        print_menu();
        int choice = get_players_choice();
        if (choice == START) {
            Game game;
            game.start();
        }  
        if (choice == INSTRUCTIONS) {
            print_InstAndKeys();
        }
        if (choice == EXIT) {
            cout << "Thanks for playing PAC-MAN!" << endl;
            exit(0);
        }
        cout << endl;
    }

    return 0;
}


int get_players_choice() {
    int choice;
    cin >> choice;

    if (choice != START && choice != INSTRUCTIONS && choice != EXIT) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }
    return choice;
}


void print_menu() {
    // Present the menu
    cout << "Welcome to Pacman!" << endl;
    cout << "1. Start a new Game" << endl;
    cout << "8. Present instructions and keys" << endl;
    cout << "9. Quit" << endl;
}

void print_InstAndKeys() {
    // Print the instructions and keys
    cout << "Instructions:" << endl;
    cout << "   Eat all the dots to win the game." << endl;
    cout << "   Use the keys to move." << endl;
    cout << "Keys:" << endl;
    cout << "   w or W arrow - move up" << endl;
    cout << "   x or X arrow - move down" << endl;
    cout << "   a or A arrow - move left" << endl;
    cout << "   d or D arrow - move right" << endl;
    cout << "   s or S arrow - stay" << endl;
}
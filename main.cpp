#include <iostream>
#include <cstdlib>
#include "Board.h"
#include "Game.h"
#include "UI.h"

using namespace std;

int main() {

    while (true) {

        UI::print_menu();
        int choice = UI::get_players_choice();
        switch (choice) {
        case START:
        {
            Game game;
            game.start();
            break;
        }
        case INSTRUCTIONS:
            UI::print_InstAndKeys();
            break;
        case EXIT:
            cout << "Thanks for playing PAC-MAN!" << endl;
            exit(0);
            break;
        } 
        cout << endl;
    }
    return 0;
}



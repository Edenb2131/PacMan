#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "Board.h"
#include "Game.h"
#include "UI.h"
#include "FileHandler.h"

using namespace std;

int main() {

    while (true) {

        UI::print_menu();
        int choice = UI::get_players_choice();

        switch (choice) {
        case START:
        {
            UI::print_difficulty_menu();
            int difficulty = UI::get_players_choice_for_diff();

            Game game;
            game.setDifficulty(difficulty);
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



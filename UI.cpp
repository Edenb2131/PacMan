#include "UI.h"
#include "Game.h"
using namespace std;

int UI::get_players_choice() {
    int choice;

    cin >> choice;

    while (choice != START && choice != INSTRUCTIONS && choice != EXIT) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }
    return choice;
}

int UI::get_players_choice_for_diff() {
    int choice;

    cin >> choice;

    while (choice != BEST && choice != GOOD && choice != NOVICE) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }
    return choice;
}

int UI::get_players_choice_for_maps() {
    int choice;

    cin >> choice;

    while (choice != BEST && choice != GOOD && choice != NOVICE) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }
    return choice;
}

std::string UI::get_map_name() {
    
    cout << "Please enter the name of the selected screen: ";
    std::string result;
    cin >> result;
    cout << "\nLoading screen " << result;
    return result;
}


void UI::print_menu() {
    // Present the menu
    cout << "Welcome to Pacman!" << endl;
    cout << "1. Start a new Game" << endl;
    cout << "8. Present instructions and keys" << endl;
    cout << "9. Quit" << endl;
}

void UI::print_difficulty_menu() {
    // Present the difficulty menu
    cout << "Please choose a difficulty level:" << endl;
    cout << "1. Best" << endl;
    cout << "2. GOOD" << endl;
    cout << "3. NOVICE" << endl;
}

void UI::print_InstAndKeys() {
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

void UI::print_game_maps_choice(){
    // print the options of maps
    cout << "Please chose how you wish two play: " << endl;
    cout << "1. Play countinuesly throw the levels" << endl;
    cout << "2. Play on a random map" << endl;
    cout << "3. Play on a map of your choice" << endl;

}
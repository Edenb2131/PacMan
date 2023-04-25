#include "Game.h"
#include "Ghost.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

void clrscreen();                                       // prototype
bool check_if_hit_obstacle(int x, int y ,Board &board); // prototype

void Game::print_menu() {
    // Present the menu
    cout << "Welcome to Pacman!" << endl;
    cout << "1. Start a new Game" << endl;
    cout << "8. Present instructions and keys" << endl;
    cout << "9. Quit" << endl;
}

Game::Game() {
    ghosts[0] = new Ghost(GHOST_1_X_POS, GHOST_1_Y_POS);
    ghosts[1] = new Ghost(GHOST_2_X_POS, GHOST_2_Y_POS);
    print_menu();
    int choice = get_players_choice();
    score = 0;
    while (true) {
        // Start a new game
        if (choice == START)
            start();
        if (choice == INSTRUCTIONS)
            print_InstAndKeys();
        if (choice == EXIT) {
            cout << "Thanks for playing PAC-MAN!" << endl;
            exit(0);
        }
        cout << endl;

        print_menu();
        choice = get_players_choice();
    }
}

Game::~Game() {
    for (int i = 0; i < NUMBER_OF_GHOSTS; i++)
        delete(ghosts[i]);
}

int Game::get_players_choice() {
    int choice;
    cin >> choice;

    if (choice != START && choice != INSTRUCTIONS && choice != EXIT) {
        cout << "Invalid choice. Please try again." << endl;
        cin >> choice;
    }
    return choice;
}


void Game::start() {
    // Start the game
    Board board(pacman.get_lives(), score);

    // Main game loop
    while (pacman.get_lives() > 0) {

        // Get starting proporties for Pac-Man
        int pacman_x = pacman.get_x_pos();
        int pacman_y = pacman.get_y_pos();
        int lives = pacman.get_lives();
        
        cin.clear(); // This is to flush the buffer
        char d = pacman.get_direction();

        clrscreen();
        board.print(pacman.get_lives(), score);

        // play 1 life
        play(pacman_x, pacman_y, d, board);
        
        // Set life for Pac-Man
        pacman.set_lives(--lives);

        // Annpuncing that life has been taken
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

// TODO: change packman position to struct
void Game::play(int x, int y, char direction, Board& board) {

    while (!check_if_hit_obstacle(x, y, board)) {

        // Handle ghosts
        ghosts[0]->move(board);
        ghosts[1]->move(board);

        if (_kbhit())
            direction = _getch();

        switch (direction) {
        case RIGHT_LOWER_CASE: 
            ++x;
            break;
        case RIGHT_UPPER_CASE:
            ++x;
            break;

        case UP_LOWER_CASE:
            --y;
            break;
        case UP_UPPER_CASE:
            --y;
            break;

        case LEFT_LOWER_CASE:
            --x;
            break;

        case LEFT_UPPER_CASE:
            --x;
            break;

        case DOWN_LOWER_CASE:
            ++y;
            break;

        case DOWN_UPPER_CASE:
            ++y;
            break;

        case STAY_LOWER_CASE:
            break;

        case STAY_UPPER_CASE:
            break;

        default:
            direction = STAY_LOWER_CASE;
            break;
        }

        // handeling moving between right - left walls
        // TODO: move to consts
        if (x == 0 && y == 11 && direction == LEFT_LOWER_CASE)
            x = WIDTH-1;

        if (x == WIDTH-1 && y == 11 && direction == RIGHT_LOWER_CASE)
            x = 0;

        Game::gotoxy(x, y);
        char boardCell = board.getCell(x,y);
        cout << pacman.get_pacman_char() << endl;

        Sleep(200);

        // If eat breadcrumbs then chnage the score
        if (boardCell == BREADCRUMB) {
            board.setCell(x, y, EMPTY);
            boardCell = EMPTY;
            score++;
        }
 
        Game::gotoxy(x, y);
        cout << boardCell << endl;

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
    cout << "   w or W arrow - move up" << endl;
    cout << "   x or X arrow - move down" << endl;
    cout << "   a or A arrow - move left" << endl;
    cout << "   d or D arrow - move right" << endl;
    cout << "   s or S arrow - stay" << endl;
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
bool check_if_hit_obstacle(int x, int y, Board &board) {
    
    // Check if hit the boarder or # sign
    if (x != 0 && y != 11 || x !=79 && y !=11) // To make sure this wont inturpt swtiching sides
        if (x == 0 || x == 79 || y == 0 || y == 24)
            return true;
    
    // Check if hit a # sign (wall)
    if (board.getCell(x,y) == '#')
        return true;

    // Check if hit a $ sign (ghost)
    if (board.getCell(x,y) == '$')
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
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
    ghosts[0] = new Ghost(GHOST_1_X_STARTING_POS, GHOST_1_Y_STARTING_POS);
    ghosts[1] = new Ghost(GHOST_2_X_STARTING_POS, GHOST_2_Y_STARTING_POS);
    print_menu();
    int choice = get_players_choice();
    total_score = 0;
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

bool Game::isGamePinished(bool& didPlayerWin) {
    return pacman.get_lives() <= 0 || didPlayerWin;
 }


void Game::start() {
    // Start the game
    Board board(pacman.get_lives(), total_score);
    bool didPlayerWin = false;

    // Main game loop
    while (!isGamePinished(didPlayerWin)) {
        // Get starting proporties for Pac-Man
        int pacman_x = pacman.get_x_pos();
        int pacman_y = pacman.get_y_pos();
        int lives = pacman.get_lives();
        
        cin.clear(); // This is to flush the buffer
        char d = pacman.get_direction();

        clrscreen();
        board.print(pacman.get_lives(), total_score);

        // play 1 life
        GameStatus status = play(pacman_x, pacman_y, d, board);
        
        if (status == GameStatus::PlayerLost) {
            // Set life for Pac-Man
            pacman.set_lives(--lives);

            // move both ghosts to their strting position
            for (auto& ghost : ghosts) {
                ghost->moveToStartingPosition(board);
            }

            // Annpuncing that life has been taken
            gotoxy(WIDTH / 2 - 10, HEIGHT - 1);
            cout << "You Lost a life " << endl;

            Sleep(2000);

        }
        else if (status == GameStatus::PlayerWon) {
            didPlayerWin = true;
        }
    }

    // showing end message and initial score and pacmen's lives
    player_end_message(didPlayerWin);
    initLivesAndScore();
    clrscreen();
}

void UpdatePositionAccordingToUser(int& x, int& y, char prev_direction, char& direction, bool& is_screen_frozen) {
    
    if (is_screen_frozen && direction != SCREEN_FREEZE) {
        return;
    }
    switch (direction) { 
    case SCREEN_FREEZE:
        is_screen_frozen = !is_screen_frozen;
        direction = prev_direction;
        break;
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
}

GameStatus Game::play(int x, int y, char direction, Board& board) {

    bool is_screen_frozen = false;
    
    while (!check_if_hit_obstacle(x, y, board) && total_score < NUMBER_OF_BREADCRUMBS) {

        int prev_x = x, prev_y = y;
        char prev_direction = direction;
        
        if (_kbhit())
            direction = _getch();
        UpdatePositionAccordingToUser(x, y, prev_direction, direction, is_screen_frozen);
        if (is_screen_frozen) {
            Sleep(200);
            continue;
        }

        // If eat breadcrumbs then chnage the score
        char boardCell = board.getCell(prev_x, prev_y);
        if (boardCell == BREADCRUMB) {
            board.setCell(prev_x, prev_y, EMPTY);
            boardCell = EMPTY;
            total_score++;
        }
        Game::gotoxy(prev_x, prev_y);
        cout << boardCell << endl;      
        
        // handeling moving between right - left walls
        if (x == 0 && y == 11 && direction == LEFT_LOWER_CASE)
            x = WIDTH-1;

        if (x == WIDTH-1 && y == 11 && direction == RIGHT_LOWER_CASE)
            x = 0;

        Game::gotoxy(x, y);
        cout << pacman.get_pacman_char() << endl;

        // Handle ghosts
        for (auto& ghost : ghosts) {
            ghost->move(board);
        }

        // Update the score on board
        board.update_score_board(total_score);

        Sleep(200);
    }

    if (total_score >= NUMBER_OF_BREADCRUMBS) {
        return GameStatus::PlayerWon;
    }
    return GameStatus::PlayerLost;
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


void Game::player_end_message(bool& didPlayerWin) {
    clrscreen();
    if (!didPlayerWin) {
        // Game has ended - 3 lives were over
        cout << "YOU LOST THE GAME!" << endl;
    }
    else {
        // Game has ended - player won
        cout << "YOU WON THE GAME!" << endl;
    }
    char ch;
    cout << "Your score is: " << total_score << endl;;
    cout << "Press any key to go back to main menu!" << endl;
    cin >> ch;
}

void Game::initLivesAndScore() {
    pacman.set_lives(MAX_NUMBER_OF_LIVES);
    total_score = 0;
}
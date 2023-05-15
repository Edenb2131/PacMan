#include "Game.h"
#include "Ghost.h"
#include <Windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

void clrscreen();  // prototype
void updateBoardAndScreen(int x, int y, Board* board, Fruit* fruit, char ch);

Game::Game() {
    board = new Board(pacman.get_lives(), total_score);
    total_score = 0;

}

Game::~Game() {
    delete(board);
}


bool Game::isGameFinished(bool& didPlayerWin) {
    return pacman.get_lives() <= 0 || didPlayerWin;
 }


void Game::setDifficulty(int _difficulty) {
    difficulty = _difficulty;
}

string Game::getDifficultyString(){
    switch (difficulty) {
    case 1:
        // Ghosts try to chase the pacmen
        return "Best";
    case 2: 
        // Ghosts try to chase the pacmen, but sometimes they get confused (randomly once in ~~20 moves)
        return "Medium";
    case 3:
        // Ghosts just move on screen with a random direction every 20 moves
        return "Hard";
    default:
        return "Unknown";
    }
}

void Game::getDifficultyFromUser(){
    int level;
    cout << "Please choose a level (1-3): ";
    cin >> level;
    while (level < 1 || level > 3) {
        cout << "Please choose a level (1-3): ";
        cin >> level;
    }
    setDifficulty(level);
}

void Game::start() {
    // Start the game
    bool didPlayerWin = false;

    // Main game loop
    while (!isGameFinished(didPlayerWin)) {
        // Get starting proporties for Pac-Man
        int pacman_x = pacman.get_x_pos();
        int pacman_y = pacman.get_y_pos();
        int lives = pacman.get_lives();
        
        cin.clear(); // This is to flush the buffer
        char direction = pacman.get_direction();

        clrscreen();
        board->print(pacman.get_lives(), total_score);
        fruit = new Fruit();
        // play 1 life
        GameStatus status = playOneRound(pacman_x, pacman_y, direction);
        
        if (status == GameStatus::PlayerLost) {
            // Set life for Pac-Man
            pacman.set_lives(--lives);

            // move all ghosts to their strting position
            ghostManager.moveGhostsToStartingPosition(board);
            
            // Announcing that life has been taken
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
    clrscreen();
}

void Game::updatePositionAccordingToUser(int& x, int& y, char prev_direction, char& direction, bool& is_screen_frozen) {
    
    if (is_screen_frozen && direction != SCREEN_FREEZE) {
        return;
    }
    switch (direction) { 
    case SCREEN_FREEZE:
        is_screen_frozen = !is_screen_frozen;

        if (is_screen_frozen) {
            gotoxy(23, HEIGHT - 1);
            cout << "Game pauesed, press ESC to continue";
        }
        else {
            gotoxy(23, HEIGHT - 1);
            cout << "                                    ";
        }

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

GameStatus Game::playOneRound(int x, int y, char direction) {

    bool is_screen_frozen = false;
    int prev_x_fruit, prev_y_fruit;
    int prev_x, prev_y;

    while (!check_if_hit_obstacle(x, y) && total_score < board->gettotalNumberOfBreadcrumbs()) {

        int prev_x = x, prev_y = y;
        prev_x_fruit = fruit->getX(), prev_y_fruit = fruit->getY();
        char prev_direction = direction;
        bool didCollideWithFruit = false;
        
        if (_kbhit())
            direction = _getch();

        updatePositionAccordingToUser(x, y, prev_direction, direction, is_screen_frozen);
        if (is_screen_frozen) {
            Sleep(200);
            continue;
        }

        // If eat breadcrumbs then chnage the score
        char boardCell = board->getCell(prev_x, prev_y);
        if (boardCell == BREADCRUMB) {
            board->setCell(prev_x, prev_y, EMPTY);
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

        // Handle Fruit
        didCollideWithFruit = fruit->moveAndCheckCollision(prev_x, prev_y, x, y, board);
        if(didCollideWithFruit){
            //board->setCell(fruit->getX(), fruit->getY(), boardCell);
            //Game::gotoxy(prev_x, prev_y);
            //cout << boardCell << endl;

            updateBoardAndScreen(fruit->getX(), fruit->getY(), board, fruit, boardCell);
            total_score += fruit->get_symbol();

            // Make a new fruit after we ate the last one
            delete fruit;
            fruit = new Fruit();
        }

        // Handle a cycle time for a fruit
        if(fruit->cycle_time == 0){
            
            // Make sure we impement the rellevent char on the board
            char FruitCell = board->getCell(prev_x_fruit, prev_y_fruit);
            updateBoardAndScreen(prev_x_fruit, prev_y_fruit, board, fruit, FruitCell);

            // Make a new fruit after sometime passed
            delete fruit;
            fruit = new Fruit();
        }


        // Handle ghosts
        bool didCollideWithGhost = ghostManager.moveAndCheckCollision(prev_x, prev_y, x, y, board);
        if (didCollideWithGhost) {
            return GameStatus::PlayerLost;
        }

        // Update the score on board
        board->update_score_board(total_score);

        Sleep(200);
    }

    // Handle dismissing the fruit from screen after lost of life
    fruit->moveAndCheckCollision(prev_x, prev_y, x, y, board);
    char FruitCell = board->getCell(prev_x_fruit, prev_y_fruit);
    updateBoardAndScreen(fruit->getX(), fruit->getY(), board, fruit, FruitCell);


    if (total_score >= board->gettotalNumberOfBreadcrumbs()) {
        return GameStatus::PlayerWon;
    }
    return GameStatus::PlayerLost;
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
bool Game::check_if_hit_obstacle(int x, int y) {
    
    // Check if hit the boarder or # sign
    if (x != 0 && y != 11 || x !=79 && y !=11) // To make sure this wont inturpt swtiching sides
        if (x == 0 || x == 79 || y == 0 || y == 24)
            return true;
    
    // Check if hit a # sign (wall)
    if (board->getCell(x,y) == '#')
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
    cout << "Your score is: " << total_score << endl;;
    cout << "Press any key to go back to main menu!" << endl;
    // Wait for a keyboard hit from the user
    while (!_kbhit()) {
        Sleep(100);
    };
    // Consume the keyboard hit
    _getch();

    // clear the screen for a fresh game (:
    clrscreen();
}


void updateBoardAndScreen(int x, int y, Board* board , Fruit* fruit ,char ch) {

    // Make sure we impement the rellevent char on the board

    board->setCell(fruit->getX(), fruit->getY(), ch);

    Game::gotoxy(fruit->getX(), fruit->getY());
    cout << ch << endl;

}

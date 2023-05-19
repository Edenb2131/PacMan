#include "Fruit.h"
#include "Game.h"

using namespace std;

Fruit::Fruit() : Creature(4)
{
    fruitValue = rand() % 5 + 5;
    hoverAbove = ' ';
    direction = DOWN_LOWER_CASE;
}

Fruit::Fruit(int x, int y, int speed) : Creature(x, y, speed)
{
    fruitValue = rand() % 5 + 5;
}

Fruit::~Fruit()
{
}

char Fruit::GetCreatureChar(){

    if (fruitValue <= 9 && fruitValue >= 5) {
        return '0' + fruitValue;
    }
    return '5';
    //TODO: why 5?
}

void Fruit::moveToStartingPosition(Board* board)
{
    board->setCell(Creature::getX(), Creature::getY(), fruitValue);
}

void Fruit::ResetFruit() {
    x = rand() % 70 + 1;
    y = rand() % 20 + 1;
    fruitValue = rand() % 5 + 5;
    cycle_time = 10;    //TODO: make not arab.
}

void Fruit::UpdatePosition(Board* board)
{
    if (cycle_time == 0) {
        ResetFruit();
        return;
    }
    cycle_time--;

    int new_x = getX();
    int new_y = getY();

    // Check the direction and move accordingly
    if (direction == DOWN_LOWER_CASE) {
        new_y = getY() + 1;
    }
    else if (direction == UP_LOWER_CASE) {
        new_y = getY() - 1;
    }
    else if (direction == RIGHT_LOWER_CASE) {
        new_x = getX() + 1;
    }
    else if (direction == LEFT_LOWER_CASE) {
        new_x = getX() - 1;
    }

    // Check if the new position collides with a wall, and if so, change the direction
    if (board->getCell(new_x, new_y) == '#') {
        while (true) {
            int new_direction = rand() % 4; // Generate a random number between 0 and 3
            if (new_direction == 0 && getY() < HEIGHT - 3 && board->getCell(getX(), getY() + 1) != '#') { // Try moving down
                direction = DOWN_LOWER_CASE;
                setY(getY() + 1);
                break;
            }
            else if (new_direction == 1 && getY() > 1 && board->getCell(getX(), getY() - 1) != '#') { // Try moving up
                direction = UP_LOWER_CASE;
                setY(getY() - 1);
                break;
            }
            else if (new_direction == 2 && getX() < WIDTH - 2 && board->getCell(getX() + 1, getY()) != '#') { // Try moving right
                direction = RIGHT_LOWER_CASE;
                setX(getX() + 1);
                break;
            }
            else if (new_direction == 3 && getX() > 1 && board->getCell(getX() - 1, getY()) != '#') { // Try moving left
                direction = LEFT_LOWER_CASE;
                setX(getX() - 1);
                break;
            }
        }
        if (board->getCell(new_x, new_y) == '$') {
            cycle_time = 0;
        }
    }
    else { // Move to the new position
        setX(new_x);
        setY(new_y);
    }
}

void Fruit::disappear(Board* board) {
    if (hoverAbove == '.' || hoverAbove == ' ') {
        board->setCell(this->getX(), this->getY(), this->hoverAbove);
        Game::gotoxy(getX(), getY());
        cout << hoverAbove;
    }
}


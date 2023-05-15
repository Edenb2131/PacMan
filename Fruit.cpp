#include "Fruit.h"

using namespace std;

Fruit::Fruit() : Creature()
{
    symbol = rand() % 5 + 5;
    Creature::setShouldUpdate(4);
    hoverAbove = ' ';
    direction = DOWN_LOWER_CASE;
}

Fruit::Fruit(int x, int y, int speed) : Creature(x, y, speed)
{
    symbol = rand() % 5 + 5;
}

Fruit::~Fruit()
{
}

char Fruit::get_symbol_as_char(){
    switch (symbol)
    {
    case 5:
        return '5';
        break;
    case 6:
        return '6';
        break;
    case 7:
        return '7';
        break;
    case 8:
        return '8';
        break;
    case 9:
        return '9';
        break;
    default:
        return '5';
        break;
    }
}

void Fruit::moveToStartingPosition(Board* board)
{
    board->setCell(Creature::getX(), Creature::getY(), symbol);
}

void Fruit::move(Board* board){

    if (getShouldUpdate() == FRUIT_SPEED) {
        int prev_x = getX();
        int prev_y = getY();

        // To make sure we didnt land on a wall
        while (board->getCell(prev_x, prev_y) == '#') {

            prev_x = rand() % 70 + 1;
            prev_y = rand() % 20 + 1;
        }

        char ch = board->getCell(prev_x, prev_y);

        if (ch == ' ')
            hoverAbove = ' ';
        if (ch == '.')
            hoverAbove = '.';

        board->setCell(prev_x, prev_y, hoverAbove);
        Game::gotoxy(prev_x, prev_y);
        cout << hoverAbove << endl;

        updateXY(board);

        hoverAbove = board->getCell(getX(), getY());
        board->setCell(getX(), getY(), get_symbol_as_char());
        Game::gotoxy(getX(), getY());
        cout << get_symbol_as_char() << endl;

        setShouldUpdate(0);
        cycle_time--;
    }
    else {
        int speed = getShouldUpdate();
        setShouldUpdate(++speed); // update ghosts alternately to make them move slower then pacman.
    }
}


void Fruit::updateXY(Board* board)
{
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
    }
    else { // Move to the new position
        setX(new_x);
        setY(new_y);
    }
}

bool Fruit::moveAndCheckCollision(int prev_pacman_x_pos, int prev_pacman_y_pos, int curr_pacman_x_pos, int curr_pacman_y_pos, Board* board) {

	//for (Fruit* fruit : fruits) {
		int prev_fruit_x_pos = getX();
		int prev_fruitt_y_pos = getY();

		move(board);
		int curr_fruit_x_pos = getX();
		int curr_fruit_y_pos = getY();

		if (curr_fruit_x_pos == curr_pacman_x_pos && curr_fruit_y_pos == curr_pacman_y_pos)
			return true;
		else if (prev_fruit_x_pos == curr_pacman_x_pos && curr_fruit_x_pos == prev_pacman_x_pos &&
                prev_fruitt_y_pos == curr_pacman_y_pos && curr_fruit_y_pos == prev_pacman_y_pos)
			return true;
//	}
	return false;
}


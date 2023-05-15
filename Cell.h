#ifndef PACMAN_GAME_CELL_H
#define PACMAN_GAME_CELL_H

class Cell
{
	int x;
	int y;

public:
	Cell(int x, int y) : x(x), y(y) {}
	~Cell() = default;
	int getX() { return x; }
	int getY() { return y; }
};


#endif //PACMAN_GAME_CELL_H


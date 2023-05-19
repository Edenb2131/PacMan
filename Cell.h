#ifndef PACMAN_GAME_CELL_H
#define PACMAN_GAME_CELL_H

class Cell
{
	int x;
	int y;

public:
	Cell(int x, int y) : x(x), y(y) {}
	~Cell() = default;
	void setX(int value) { x = value; }
	void setY(int value) { y = value; }
	int getX() { return x; }
	int getY() { return y; }
	bool Equals(const Cell& other) const {
		return x == other.x && y == other.y;
	}
};


#endif //PACMAN_GAME_CELL_H


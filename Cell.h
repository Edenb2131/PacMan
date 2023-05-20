#ifndef PACMAN_GAME_CELL_H
#define PACMAN_GAME_CELL_H

#include <string>

class Cell
{
	int x;
	int y;

public:
	Cell(int x, int y) : x(x), y(y) {}
	~Cell() = default;
	void setX(int value) { x = value; }
	void setY(int value) { y = value; }
	int getX() const { return x; }
	int getY() const { return y; }
	bool Equals(const Cell& other) const {
		return x == other.x && y == other.y;
	}
	bool operator==(const Cell& other) const {
		return this->Equals(other);
	}
	operator std::string() const {
		return "x=" + std::to_string(x) + "y=" + std::to_string(y);
	}
};


#endif //PACMAN_GAME_CELL_H


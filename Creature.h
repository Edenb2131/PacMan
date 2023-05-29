#pragma once

#include <random>
#include "Board.h"

class Creature
{
protected:
	int x;
	int y;
	int shouldUpdate;
	const int moveFrequency;

	virtual void UpdatePosition(Board* board, Cell pacmenPosition) = 0;
	virtual char GetCreatureChar() = 0;

public:

	char direction;
	char hoverAbove;

	Creature(int moveFrequency);
	Creature(int x, int y, int moveFrequency);
	~Creature();

	int getX() const {return x;}
	int getY() const {return y;}
	Cell getPosition() const { return Cell(x, y); }
	int getShouldUpdate() const {return shouldUpdate;}
	char get_direction() const { return direction; }

	void setX(int x);
	void setY(int y);
	void setShouldUpdate(int shouldUpdate);

	void move(Board* board, Cell pacmenPosition);
};

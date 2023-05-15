#pragma once

#include <random>

class Creature
{

	int x;
	int y;
	int shouldUpdate;

public:

	char direction;
	char hoverAbove;


	Creature();
	Creature(int x, int y, int shouldUpdate);
	~Creature();

	int getX() const {return x;}
	int getY() const {return y;}
	int getShouldUpdate() const {return shouldUpdate;}

	void setX(int x);
	void setY(int y);
	void setShouldUpdate(int shouldUpdate);

	//void move(Board* board);
	//void updateXY();
	//void moveToStartingPosition(Board* board);
};

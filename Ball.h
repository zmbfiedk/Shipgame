#pragma once

#include "Border.h"
#include "Player.h"

class Ball
{
public:
	Ball(int startX, int startY, int initialDx = 1, int initialDy = 1);

	int getX() const;
	int getY() const;
	void update(const Border& border, const Player& player);

private:
	static int angleToDy(int angleDegrees);

	int x;
	int y;
	int dx;
	int dy;
	int lastPaddleDy;
	bool hasLastPaddleDy;
};

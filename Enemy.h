#pragma once

class Enemy
{
public:
	Enemy(int x, int topY, int shapeHeight = 7);
	bool occupies(int posX, int posY) const;

private:
	int x;
	int topY;
	int shapeHeight;
};

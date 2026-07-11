#pragma once

class Enemy
{
public:
	Enemy(int x, int topY, int shapeHeight = 7);
	int getX() const;
	int getTopY() const;
	int getShapeHeight() const;
	bool occupies(int posX, int posY) const;

private:
	int x;
	int topY;
	int shapeHeight;
};

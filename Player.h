#pragma once

class Player
{
public:
	Player(int x, int topY);

	int getX() const;
	int getTopY() const;
	int getShapeHeight() const;
	void moveUp(int minY = 0);
	void moveDown(int maxHeight);
	bool occupies(int posX, int posY) const;
	int getBounceAngle(int segmentIndex) const;

private:
	int x;
	int topY;
	int shapeHeight;
};

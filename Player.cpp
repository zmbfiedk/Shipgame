#include "Player.h"

Player::Player(int x, int topY) : x(x), topY(topY), shapeHeight(7) {}

int Player::getX() const
{
	return x;
}

int Player::getTopY() const
{
	return topY;
}

int Player::getShapeHeight() const
{
	return shapeHeight;
}

void Player::moveUp(int minY)
{
	if (topY > minY)
	{
		--topY;
	}
}

void Player::moveDown(int maxHeight)
{
	if (topY + shapeHeight < maxHeight)
	{
		++topY;
	}
}

bool Player::occupies(int posX, int posY) const
{
	return posX == x && posY >= topY && posY < topY + shapeHeight;
}

int Player::getBounceAngle(int segmentIndex) const
{
	if (segmentIndex < 0 || segmentIndex >= shapeHeight)
	{
		return 0;
	}

	const int middleIndex = shapeHeight / 2;
	return (middleIndex - segmentIndex) * 15;
}

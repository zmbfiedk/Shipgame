#include "Enemy.h"

Enemy::Enemy(int x, int topY, int shapeHeight)
	: x(x), topY(topY), shapeHeight(shapeHeight)
{
}

bool Enemy::occupies(int posX, int posY) const
{
	return posX == x && posY >= topY && posY < topY + shapeHeight;
}

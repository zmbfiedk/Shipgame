#include "Ball.h"

#include <cmath>

namespace
{
	constexpr double kPi = 3.14159265358979323846;
}

Ball::Ball(int startX, int startY, int initialDx, int initialDy)
	: x(startX), y(startY), dx(initialDx >= 0 ? 1 : -1), dy(initialDy), lastPaddleDy(0), hasLastPaddleDy(false)
{
}

int Ball::getX() const
{
	return x;
}

int Ball::getY() const
{
	return y;
}

void Ball::update(const Border& border, const Player& player)
{
	int nextX = x + dx;
	int nextY = y + dy;

	if (nextY < 0 || nextY >= border.getHeight())
	{
		dy = -dy;
		nextY = y + dy;
	}

	if (dx < 0 && nextX <= player.getX() && player.occupies(player.getX(), nextY))
	{
		const int segmentIndex = nextY - player.getTopY();
		const int angle = player.getBounceAngle(segmentIndex);
		int proposedDy = angleToDy(angle);

		// If the same steep rebound repeats, soften it one step toward center.
		if (hasLastPaddleDy && proposedDy == lastPaddleDy && std::abs(proposedDy) >= 2)
		{
			proposedDy += (proposedDy > 0) ? -1 : 1;
		}

		dx = 1;
		dy = proposedDy;
		lastPaddleDy = dy;
		hasLastPaddleDy = true;

		// Keep the ball just to the right of the paddle to avoid repeated collisions.
		x = player.getX() + 1;
		y = nextY;
		return;
	}

	if (nextX < 0 || nextX >= border.getWidth())
	{
		dx = -dx;
		nextX = x + dx;
	}

	x = nextX;
	y = nextY;
}

int Ball::angleToDy(int angleDegrees)
{
	const double radians = angleDegrees * (kPi / 180.0);
	const int mappedDy = static_cast<int>(std::round(std::tan(radians) * 2.0));

	if (mappedDy > 2)
	{
		return 2;
	}
	if (mappedDy < -2)
	{
		return -2;
	}
	return mappedDy;
}

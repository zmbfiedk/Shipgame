#include "Ball.h"

#include "Enemy.h"

#include <cmath>

namespace
{
	constexpr double kPi = 3.14159265358979323846;
	constexpr double kInitialSpeed = 0.85;
	constexpr double kAcceleration = 1.01;
	constexpr double kMaxSpeed = 1.8;
}

Ball::Ball(int startX, int startY, int initialDx, int initialDy)
	: x(static_cast<double>(startX)),
	  y(static_cast<double>(startY)),
	  velocityX(static_cast<double>(initialDx >= 0 ? 1 : -1)),
	  velocityY(static_cast<double>(initialDy)),
	  speed(kInitialSpeed),
	  nextServeUp(true),
	  lastPaddleDy(0),
	  hasLastPaddleDy(false),
	  hitLeftWall(false),
	  hitRightWall(false)
{
	normalize(velocityX, velocityY);
	velocityX *= speed;
	velocityY *= speed;
}

int Ball::getX() const
{
	return static_cast<int>(std::lround(x));
}

int Ball::getY() const
{
	return static_cast<int>(std::lround(y));
}

bool Ball::hitLeftWallThisFrame() const
{
	return hitLeftWall;
}

bool Ball::hitRightWallThisFrame() const
{
	return hitRightWall;
}

void Ball::reset(int startX, int startY, bool serveTowardLeft)
{
	x = static_cast<double>(startX);
	y = static_cast<double>(startY);
	speed = kInitialSpeed;
	hitLeftWall = false;
	hitRightWall = false;
	hasLastPaddleDy = false;
	lastPaddleDy = 0;

	const double horizontalDirection = serveTowardLeft ? -1.0 : 1.0;
	const double verticalDirection = nextServeUp ? -0.35 : 0.35;
	nextServeUp = !nextServeUp;

	velocityX = horizontalDirection;
	velocityY = verticalDirection;
	normalize(velocityX, velocityY);
	velocityX *= speed;
	velocityY *= speed;
}

void Ball::update(const Border& border, const Player& player, const Enemy& enemy)
{
	hitLeftWall = false;
	hitRightWall = false;

	double nextX = x + velocityX;
	double nextY = y + velocityY;

	if (nextY < 0.0 || nextY >= static_cast<double>(border.getHeight()))
	{
		velocityY = -velocityY;
		nextY = y + velocityY;
	}

	const int nextGridY = static_cast<int>(std::lround(nextY));

	if (velocityX < 0.0 && nextX <= static_cast<double>(player.getX() + 1) && player.occupies(player.getX(), nextGridY))
	{
		const int segmentIndex = nextGridY - player.getTopY();
		const int angle = player.getBounceAngle(segmentIndex);
		double proposedVelocityY = angleToSlope(angle);

		if (hasLastPaddleDy && static_cast<int>(std::lround(proposedVelocityY * 100.0)) == lastPaddleDy && std::abs(proposedVelocityY) >= 0.5)
		{
			proposedVelocityY += (proposedVelocityY > 0.0) ? -0.1 : 0.1;
		}

		velocityX = 1.0;
		velocityY = proposedVelocityY;
		normalize(velocityX, velocityY);
		velocityX *= speed;
		velocityY *= speed;
		lastPaddleDy = static_cast<int>(std::lround(proposedVelocityY * 100.0));
		hasLastPaddleDy = true;

		x = static_cast<double>(player.getX() + 1);
		y = nextY;
		applyAcceleration();
		return;
	}

	if (velocityX > 0.0 && nextX >= static_cast<double>(enemy.getX() - 1) && enemy.occupies(enemy.getX(), nextGridY))
	{
		const int segmentIndex = nextGridY - enemy.getTopY();
		const int angle = (segmentIndex - enemy.getShapeHeight() / 2) * 15;
		double proposedVelocityY = angleToSlope(angle);

		if (hasLastPaddleDy && static_cast<int>(std::lround(proposedVelocityY * 100.0)) == lastPaddleDy && std::abs(proposedVelocityY) >= 0.5)
		{
			proposedVelocityY += (proposedVelocityY > 0.0) ? -0.1 : 0.1;
		}

		velocityX = -1.0;
		velocityY = proposedVelocityY;
		normalize(velocityX, velocityY);
		velocityX *= speed;
		velocityY *= speed;
		lastPaddleDy = static_cast<int>(std::lround(proposedVelocityY * 100.0));
		hasLastPaddleDy = true;

		x = static_cast<double>(enemy.getX() - 1);
		y = nextY;
		applyAcceleration();
		return;
	}

	if (nextX < 0.0 || nextX >= static_cast<double>(border.getWidth()))
	{
		if (nextX < 0.0)
		{
			hitLeftWall = true;
		}
		else
		{
			hitRightWall = true;
		}

		x = nextX;
		y = nextY;
		return;
	}

	x = nextX;
	y = nextY;
	applyAcceleration();
}

double Ball::angleToSlope(int angleDegrees)
{
	const double radians = angleDegrees * (kPi / 180.0);
	return std::tan(radians);
}

void Ball::normalize(double& velocityX, double& velocityY)
{
	const double length = std::sqrt(velocityX * velocityX + velocityY * velocityY);
	if (length == 0.0)
	{
		velocityX = 1.0;
		velocityY = 0.0;
		return;
	}

	velocityX /= length;
	velocityY /= length;
}

void Ball::applyAcceleration()
{
	speed *= kAcceleration;
	if (speed > kMaxSpeed)
	{
		speed = kMaxSpeed;
	}

	normalize(velocityX, velocityY);
	velocityX *= speed;
	velocityY *= speed;
}

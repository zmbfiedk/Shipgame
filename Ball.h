#pragma once

#include "Border.h"
#include "Player.h"

class Enemy;

class Ball
{
public:
	Ball(int startX, int startY, int initialDx = 1, int initialDy = 1);

	int getX() const;
	int getY() const;
	bool hitLeftWallThisFrame() const;
	bool hitRightWallThisFrame() const;
	void reset(int startX, int startY, bool serveTowardLeft);
	void update(const Border& border, const Player& player, const Enemy& enemy);

private:
	static double angleToSlope(int angleDegrees);
	static void normalize(double& velocityX, double& velocityY);
	void applyAcceleration();

	double x;
	double y;
	double velocityX;
	double velocityY;
	double speed;
	bool nextServeUp;
	int lastPaddleDy;
	bool hasLastPaddleDy;
	bool hitLeftWall;
	bool hitRightWall;
};

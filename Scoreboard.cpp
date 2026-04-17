#include "Scoreboard.h"

#include <iostream>

Scoreboard::Scoreboard() : leftWallScore(0), rightWallScore(0) {}

void Scoreboard::addLeftWallPoint()
{
	++leftWallScore;
}

void Scoreboard::addRightWallPoint()
{
	++rightWallScore;
}

int Scoreboard::getLeftWallScore() const
{
	return leftWallScore;
}

int Scoreboard::getRightWallScore() const
{
	return rightWallScore;
}

void Scoreboard::draw() const
{
	std::cout << "Left Wall Score: " << leftWallScore << " | Right Wall Score: " << rightWallScore << '\n';
}

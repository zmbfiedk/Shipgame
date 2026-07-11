#pragma once

#include <ostream>

class Scoreboard
{
public:
	Scoreboard();

	void addLeftWallPoint();
	void addRightWallPoint();
	int getLeftWallScore() const;
	int getRightWallScore() const;
	void draw(std::ostream& output) const;

private:
	int leftWallScore;
	int rightWallScore;
};

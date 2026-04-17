#pragma once

class Scoreboard
{
public:
	Scoreboard();

	void addLeftWallPoint();
	void addRightWallPoint();
	int getLeftWallScore() const;
	int getRightWallScore() const;
	void draw() const;

private:
	int leftWallScore;
	int rightWallScore;
};

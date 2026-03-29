#pragma once

#include <string>
#include <vector>

class Border
{
public:
	Border(int width = 10, int height = 10);

	int getWidth() const;
	int getHeight() const;
	void draw(const std::vector<std::string>& layer) const;

private:
	int width;
	int height;
};

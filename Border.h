#pragma once

#include <ostream>
#include <string>
#include <vector>

class Border
{
public:
	Border(int width = 10, int height = 10);

	int getWidth() const;
	int getHeight() const;
	void draw(std::ostream& output, const std::vector<std::string>& layer) const;

private:
	int width;
	int height;
};

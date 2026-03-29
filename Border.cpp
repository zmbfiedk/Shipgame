#include "Border.h"

#include <iostream>

Border::Border(int width, int height) : width(width), height(height) {}

int Border::getWidth() const
{
	return width;
}

int Border::getHeight() const
{
	return height;
}

void Border::draw(const std::vector<std::string>& layer) const
{
	for (int y = 0; y < height + 2; ++y)
	{
		for (int x = 0; x < width + 2; ++x)
		{
			const bool isEdge = (x == 0 || x == width + 1 || y == 0 || y == height + 1);
			if (isEdge)
			{
				std::cout << '#';
			}
			else
			{
				std::cout << layer[y - 1][x - 1];
			}
		}
		std::cout << '\n';
	}
}

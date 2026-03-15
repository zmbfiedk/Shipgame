#include "Border.h"

Border::Border(int width, int height) : width(width), height(height) {}

void Border::Draw() const
{
    for (int x = 1; x <= width; x++)
    {
        std::cout << "\033[1;" << x << "H#";
        std::cout << "\033[" << height << ";" << x << "H#";
    }

    for (int y = 1; y <= height; y++)
    {
        std::cout << "\033[" << y << ";1H#";
        std::cout << "\033[" << y << ";" << width << "H#";
    }
}

int Border::GetMinX() const { return 2; }
int Border::GetMaxX() const { return width - 1; }
int Border::GetMinY() const { return 2; }
int Border::GetMaxY() const { return height - 1; }
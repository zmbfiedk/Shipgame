#include "Ship.h"

Ship::Ship(int x, int y, int minX, int maxX, int minY, int maxY)
    : x(x), y(y),
    prevX(x), prevY(y),
    minX(minX), maxX(maxX),
    minY(minY), maxY(maxY)
{
}

void Ship::MoveShip(int dx, int dy)
{
    prevX = x;
    prevY = y;

    x = std::max(minX, std::min(x + dx, maxX - 2)); 
    y = std::max(minY, std::min(y + dy, maxY));
}

void Ship::Draw() const
{
    std::cout << "\033[" << y << ";" << x << "H";
    std::cout << "/^\\";
}

void Ship::ClearPrevious() const
{
    std::cout << "\033[" << prevY << ";" << prevX << "H   ";
}

int Ship::GetX() const { return x; }
int Ship::GetY() const { return y; }

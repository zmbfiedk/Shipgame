#pragma once
#include <iostream>
#include <algorithm>

class Ship
{
private:
    int x, y;
    int prevX, prevY;
    int minX, maxX, minY, maxY;

public:
    Ship(int x, int y, int minX, int maxX, int minY, int maxY);

    void MoveShip(int dx, int dy);

    void Draw() const;
    void ClearPrevious() const;

    int GetX() const;
    int GetY() const;
};
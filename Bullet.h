#pragma once
#include <iostream>

class Bullet
{
private:
    int x, y;
    int prevY;

public:
    Bullet(int x, int y);

    void Move();
    void Draw() const;
    void ClearPrevious() const;

    int GetX() const;
    int GetY() const;
};
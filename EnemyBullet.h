#pragma once
#include <iostream>

class EnemyBullet
{
private:
    int x, y;
    int prevY;

public:
    EnemyBullet(int x, int y);

    void Move();
    void Draw() const;
    void ClearPrevious() const;

    int GetX() const;
    int GetY() const;
};
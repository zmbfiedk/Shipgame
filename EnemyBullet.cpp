#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(int x, int y) : x(x), y(y), prevY(y) {}

void EnemyBullet::Move()
{
    prevY = y;
    y++;
}

void EnemyBullet::Draw() const
{
    std::cout << "\033[" << y << ";" << x << "H!";
}

void EnemyBullet::ClearPrevious() const
{
    std::cout << "\033[" << y << ";" << x << "H ";
}

int EnemyBullet::GetX() const { return x; }
int EnemyBullet::GetY() const { return y; }
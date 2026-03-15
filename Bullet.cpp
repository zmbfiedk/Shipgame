#include "Bullet.h"

Bullet::Bullet(int x, int y) : x(x), y(y), prevY(y) {}

void Bullet::Move()
{
    prevY = y;
    y--;
}

void Bullet::Draw() const
{
    std::cout << "\033[" << y << ";" << x << "H|";
}

void Bullet::ClearPrevious() const
{
    std::cout << "\033[" << y << ";" << x << "H ";
}

int Bullet::GetX() const { return x; }
int Bullet::GetY() const { return y; }
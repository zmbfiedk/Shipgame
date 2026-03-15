#include "Enemy.h"
#include <cstdlib>

namespace
{
    constexpr int kTicksPerSecond = 25;
    constexpr int kShootDelayTicks = kTicksPerSecond; // ~1 second at 25 FPS
}

Enemy::Enemy(int x, int y, EnemyType type)
    : x(x), y(y), prevY(y), type(type)
{
    switch (type)
    {
    case EnemyType::Normal: shootTimer = kShootDelayTicks; health = 1; break;
    case EnemyType::Fast:   shootTimer = kShootDelayTicks; health = 1; break;
    case EnemyType::Strong: shootTimer = kShootDelayTicks; health = 3; break;
    case EnemyType::Boss:   shootTimer = kShootDelayTicks; health = 20; break;
    }
}

bool Enemy::ReadyToShoot()
{
    shootTimer--;
    return shootTimer <= 0;
}

void Enemy::ResetShootTimer()
{
    switch (type)
    {
    case EnemyType::Normal: shootTimer = kShootDelayTicks; break;
    case EnemyType::Fast:   shootTimer = kShootDelayTicks; break;
    case EnemyType::Strong: shootTimer = kShootDelayTicks; break;
    case EnemyType::Boss:   shootTimer = kShootDelayTicks; break;
    }
}

void Enemy::Move()
{
    prevY = y;
    y++;
}

void Enemy::Draw() const
{
    std::string symbol = "<V>";
    if (type == EnemyType::Strong) symbol = "<S>";
    if (type == EnemyType::Boss)   symbol = "<B>";

    std::cout << "\033[" << y << ";" << x << "H" << symbol;
}

void Enemy::ClearPrevious() const
{
    std::cout << "\033[" << prevY << ";" << x << "H   ";
}

int Enemy::GetX() const { return x; }
int Enemy::GetY() const { return y; }
EnemyType Enemy::GetType() const { return type; }
int Enemy::GetHealth() const { return health; }

void Enemy::TakeDamage(int dmg) { health -= dmg; }
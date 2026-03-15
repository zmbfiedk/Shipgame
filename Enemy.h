#pragma once
#include <iostream>

enum class EnemyType { Normal, Fast, Strong, Boss };

class Enemy
{
private:
    int x, y;
    int prevY;
    int shootTimer;
    EnemyType type;
    int health;

public:
    Enemy(int x, int y, EnemyType type = EnemyType::Normal);

    bool ReadyToShoot();
    void ResetShootTimer();
    void Move();
    void Draw() const;
    void ClearPrevious() const;

    int GetX() const;
    int GetY() const;
    EnemyType GetType() const;
    int GetHealth() const;
    void TakeDamage(int dmg);
};
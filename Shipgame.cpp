#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "Border.h"
#include "Ship.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "WaveManager.h"

int main()
{
    srand((unsigned)time(0));

    constexpr int borderWidth = 52;
    constexpr int borderHeight = 22;
    constexpr int enemyWidth = 3;
    constexpr int playerShootDelayTicks = 6;

    std::cout << "\033[?25l"; // hide cursor

    Border border(borderWidth, borderHeight);
    border.Draw();

    Ship ship(borderWidth / 2, border.GetMaxY() - 1, border.GetMinX(), border.GetMaxX(), border.GetMinY(), border.GetMaxY());

    WaveManager waveManager;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;
    std::vector<EnemyBullet> enemyBullets;

    int score = 0;
    int lives = 3;
    bool running = true;
    bool playerWon = false;
    int playerShootCooldown = 0;

    waveManager.SpawnWave(enemies, border);

    while (running)
    {
        // INPUT
        if (_kbhit())
        {
            char key = _getch();
            if (key == 'a') ship.MoveShip(-1, 0);
            if (key == 'd') ship.MoveShip(1, 0);
            if (key == 'w') ship.MoveShip(0, -1);
            if (key == 's') ship.MoveShip(0, 1);
            if (key == ' ' && playerShootCooldown == 0)
            {
                bullets.emplace_back(ship.GetX() + 1, ship.GetY() - 1);
                playerShootCooldown = playerShootDelayTicks;
            }
            if (key == 27) running = false;
        }

        if (playerShootCooldown > 0)
        {
            --playerShootCooldown;
        }

        // SPAWN NEW WAVE IF NONE
        if (enemies.empty())
        {
            if (waveManager.HasMoreWaves())
            {
                waveManager.SpawnWave(enemies, border);
            }
            else
            {
                playerWon = true;
                running = false;
            }
        }

        // CLEAR OLD POSITIONS
        ship.ClearPrevious();
        for (auto& b : bullets) b.ClearPrevious();
        for (auto& e : enemies) e.ClearPrevious();
        for (auto& b : enemyBullets) b.ClearPrevious();

        // MOVE BULLETS
        for (auto& b : bullets) b.Move();
        for (auto& b : enemyBullets) b.Move();

        // ENEMY SHOOT + MOVE
        for (auto& e : enemies)
        {
            if (enemyBullets.empty() && e.ReadyToShoot())
            {
                if (e.GetY() < border.GetMaxY())
                {
                    enemyBullets.emplace_back(e.GetX() + 1, e.GetY() + 1);
                }
                e.ResetShootTimer();
                e.Move();
            }
        }

        // BULLET ↔ BULLET COLLISION
        for (auto b = bullets.begin(); b != bullets.end();)
        {
            bool collided = false;
            for (auto eb = enemyBullets.begin(); eb != enemyBullets.end();)
            {
                if (b->GetX() == eb->GetX() && b->GetY() == eb->GetY())
                {
                    eb = enemyBullets.erase(eb);
                    collided = true;
                    break;
                }
                else
                {
                    ++eb;
                }
            }

            if (collided)
            {
                b = bullets.erase(b);
            }
            else
            {
                ++b;
            }
        }

        // BULLET → ENEMY COLLISION
        for (auto b = bullets.begin(); b != bullets.end();)
        {
            bool hit = false;
            for (auto e = enemies.begin(); e != enemies.end();)
            {
                if (b->GetY() == e->GetY() &&
                    b->GetX() >= e->GetX() &&
                    b->GetX() <= e->GetX() + enemyWidth - 1)
                {
                    hit = true;
                    score += (e->GetType() == EnemyType::Boss) ? 100 : 10;
                    std::cout << "\033[" << e->GetY() << ";" << e->GetX() << "H   ";
                    e = enemies.erase(e);
                    break;
                }
                else ++e;
            }
            if (hit) b = bullets.erase(b); else ++b;
        }

        // ENEMY BULLET → PLAYER COLLISION
        for (auto b = enemyBullets.begin(); b != enemyBullets.end();)
        {
            if (b->GetY() == ship.GetY() &&
                b->GetX() >= ship.GetX() &&
                b->GetX() <= ship.GetX() + 2)
            {
                lives--;
                b = enemyBullets.erase(b);
                if (lives <= 0) running = false;
            }
            else ++b;
        }

        // ENEMY → PLAYER COLLISION
        for (const auto& e : enemies)
        {
            const bool sameRow = e.GetY() == ship.GetY();
            const bool overlapsShip = e.GetX() <= ship.GetX() + 2 &&
                e.GetX() + enemyWidth - 1 >= ship.GetX();

            if (sameRow && overlapsShip)
            {
                lives = 0;
                running = false;
                break;
            }
        }

        // REMOVE OFFSCREEN BULLETS
        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [&](Bullet& b) { return b.GetY() <= border.GetMinY() - 1; }),
            bullets.end());

        enemyBullets.erase(
            std::remove_if(enemyBullets.begin(), enemyBullets.end(),
                [&](EnemyBullet& b) { return b.GetY() >= border.GetMaxY() + 1; }),
            enemyBullets.end());

        enemies.erase(
            std::remove_if(enemies.begin(), enemies.end(),
                [&](Enemy& e) { return e.GetY() >= border.GetMaxY(); }),
            enemies.end());

        // DRAW EVERYTHING
        ship.Draw();
        for (auto& b : bullets) b.Draw();
        for (auto& e : enemies) e.Draw();
        for (auto& b : enemyBullets) b.Draw();

        // UI
        std::cout << "\033[1;3HScore: " << score;
        std::cout << "\033[1;20HLives: " << lives;
        std::cout << "\033[1;35HWave: " << (std::min)(waveManager.GetWave() - 1, waveManager.GetMaxWaves());

        Sleep(40);
    }

    if (playerWon)
    {
        std::cout << "\033[13;25HYOU WIN!";
    }
    else
    {
        std::cout << "\033[13;25HGAME OVER";
    }
    std::cout << "\033[14;25HScore: " << score;
    std::cout << "\033[?25h"; // show cursor again

    return 0;
}
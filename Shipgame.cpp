#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>
#include <algorithm>

#include "Border.h"
#include "Ship.h"
#include "Bullet.h"

int main()
{
    Border border(60, 25);

    Ship ship(
        30,
        20,
        border.GetMinX(),
        border.GetMaxX(),
        border.GetMinY(),
        border.GetMaxY()
    );

    std::vector<Bullet> bullets;

    bool running = true;

    border.Draw(); // Draw once

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

            if (key == ' ')
                bullets.emplace_back(ship.GetX() + 1, ship.GetY() - 1);

            if (key == 27)
                running = false;
        }

        ship.ClearPrevious();
        for (auto& bullet : bullets)
            bullet.ClearPrevious();

        for (auto& bullet : bullets)
            bullet.Move();

        bullets.erase(
            std::remove_if(bullets.begin(), bullets.end(),
                [&](Bullet& b) { return b.GetY() <= border.GetMinY(); }),
            bullets.end());

        ship.Draw();
        for (const auto& bullet : bullets)
            bullet.Draw();

        Sleep(40);
    }

    return 0;
}

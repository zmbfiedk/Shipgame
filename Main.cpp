#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <conio.h>
#include "Border.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"

int main()
{
	Border border(50, 14);
	Player player(0, 2);
	Enemy enemy(border.getWidth() - 1, 2);
	Ball ball(player.getX() + 2, player.getTopY() + player.getShapeHeight() / 2, 1, 1);
	bool running = true;
	const auto frameDuration = std::chrono::milliseconds(60);
	auto nextFrameTime = std::chrono::steady_clock::now();

	while (running)
	{
		while (_kbhit())
		{
			const int key = _getch();
			if (key == 'q' || key == 'Q')
			{
				running = false;
			}
			else if (key == 'w' || key == 'W')
			{
				player.moveUp();
			}
			else if (key == 's' || key == 'S')
			{
				player.moveDown(border.getHeight());
			}
			else if (key == 0 || key == 224)
			{
				const int arrowKey = _getch();
				if (arrowKey == 72)
				{
					player.moveUp();
				}
				else if (arrowKey == 80)
				{
					player.moveDown(border.getHeight());
				}
			}
		}

		if (!running)
		{
			break;
		}

		ball.update(border, player);

		std::vector<std::string> grid(border.getHeight(), std::string(border.getWidth(), ' '));

		for (int y = 0; y < border.getHeight(); ++y)
		{
			for (int x = 0; x < border.getWidth(); ++x)
			{
				if (player.occupies(x, y) || enemy.occupies(x, y))
				{
					grid[y][x] = '|';
				}
			}
		}

		if (ball.getX() >= 0 && ball.getX() < border.getWidth() && ball.getY() >= 0 && ball.getY() < border.getHeight())
		{
			grid[ball.getY()][ball.getX()] = 'o';
		}

		system("cls");
		border.draw(grid);
		std::cout << "\nControls: W/Up = move up, S/Down = move down, Q = quit\n";

		nextFrameTime += frameDuration;
		std::this_thread::sleep_until(nextFrameTime);
	}

	return 0;
}
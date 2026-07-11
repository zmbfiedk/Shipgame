#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <sstream>
#include <conio.h>
#include <windows.h>
#include "Border.h"
#include "Player.h"
#include "Enemy.h"
#include "Ball.h"
#include "Scoreboard.h"

namespace
{
	void clearConsole(HANDLE consoleHandle)
	{
		CONSOLE_SCREEN_BUFFER_INFO consoleInfo{};
		if (!GetConsoleScreenBufferInfo(consoleHandle, &consoleInfo))
		{
			return;
		}

		const DWORD cellCount = static_cast<DWORD>(consoleInfo.dwSize.X) * static_cast<DWORD>(consoleInfo.dwSize.Y);
		const COORD homePosition{ 0, 0 };
		DWORD written = 0;

		FillConsoleOutputCharacterA(consoleHandle, ' ', cellCount, homePosition, &written);
		FillConsoleOutputAttribute(consoleHandle, consoleInfo.wAttributes, cellCount, homePosition, &written);
		SetConsoleCursorPosition(consoleHandle, homePosition);
	}
}

int main()
{
	const HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	Border border(50, 14);
	Player player(0, 2);
	Enemy enemy(border.getWidth() - 1, 2);
	Ball ball(player.getX() + 2, player.getTopY() + player.getShapeHeight() / 2, 1, 1);
	Scoreboard scoreboard;
	bool running = true;
	const auto frameDuration = std::chrono::milliseconds(60);
	auto nextFrameTime = std::chrono::steady_clock::now();

	clearConsole(consoleHandle);

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

		if (ball.hitLeftWallThisFrame())
		{
			scoreboard.addLeftWallPoint();
		}
		if (ball.hitRightWallThisFrame())
		{
			scoreboard.addRightWallPoint();
		}

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

		std::ostringstream frame;
		COORD cursorPosition{ 0, 0 };
		SetConsoleCursorPosition(consoleHandle, cursorPosition);
		border.draw(frame, grid);
		scoreboard.draw(frame);
		frame << "Controls: W/Up = move up, S/Down = move down, Q = quit\n";
		std::cout << frame.str() << std::flush;

		nextFrameTime += frameDuration;
		std::this_thread::sleep_until(nextFrameTime);
	}

	return 0;
}
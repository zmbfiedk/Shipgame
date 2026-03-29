#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <conio.h>
#include "Border.h"
#include "Player.h"
#include "Enemy.h"

int main()
{
	Border border(30, 10);
	Player player(0, 2);
	Enemy enemy(border.getWidth() - 1, 2);
	bool running = true;

	while (running)
	{
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

		system("cls");
		border.draw(grid);
		std::cout << "\nControls: W/Up = move up, S/Down = move down, Q = quit\n";

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

	return 0;
}
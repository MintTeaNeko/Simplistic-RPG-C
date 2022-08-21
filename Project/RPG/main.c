#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define MAPX 8
#define MAPY 8

bool playerWasPlaced = false, running = true;
int enemyDamage = 20;
int px = 1, py = 1, tilenum = 0;
float playerHealth = 100;
int map[MAPY][MAPX] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 8, 1, 0, 6, 5, 6, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 6, 0, 6, 0, 1,
	1, 0, 6, 0, 0, 0, 0, 1,
	1, 1, 1, 0, 1, 0, 6, 1,
	1, 5, 6, 0, 1, 0, 7, 1,
	1, 1, 1, 1, 1, 1, 1, 1
};

void MoveDir(char dir);
void UpdateMap();

void main()
{
	srand(time(NULL));
	char dir;

	while (running)
	{
		UpdateMap();
		printf("enter a direction (w, a, s, d): ");
		scanf_s(" %c", &dir, 1);
		MoveDir(dir);
	}
}

void MoveDir(char dir)
{
	int newX = px, newY = py;
	switch (dir)
	{
		case 'w':
			newY -= 1;
			break;

		case 'a':
			newX -= 1;
			break;

		case 's':
			newY += 1;
			break;

		case 'd':
			newX += 1;
			break;
	}

	switch (map[newY][newX])
	{
		case 5:
		{
			enemyDamage = enemyDamage < 5 ? enemyDamage / (rand() % 5) : 5;
			map[newY][newX] = 4;
			break;
		}

		case 6:
		{
			playerHealth -= rand() % enemyDamage;
			if (playerHealth <= 0)
			{
				running = false;
				printf("GameOver!");
				return;
			}
			map[newY][newX] = 0;
			break;
		}

		case 7:
		{
			playerHealth += 10;

			if (playerHealth > 100)
			{
				playerHealth = 100;
			}

			map[newY][newX] = 9;
			break;
		}

		case 1:
		{
			return;
		}
	}
	
	map[py][px] = tilenum;
	tilenum = map[newY][newX];
	map[newY][newX] = 2;
	px = newX; py = newY;
}

void UpdateMap()
{
	for (int y = 0; y < MAPY; y++)
	{
		for (int x = 0; x < MAPX; x++)
		{
			int tile = map[y][x];
			if (tile == 8)
			{
				if (!playerWasPlaced)
				{
					playerWasPlaced = true;
					map[y][x] = 2;
					px = x; py = y;
					tile = 2;
				}
				else
				{
					map[y][x] = 0;
					tile = 0;
				}
			}

			printf("%d ", tile);
		}
		
		printf("\n");
	}

	printf("Current health %f", playerHealth);
	printf("\n");
}

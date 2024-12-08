#include <fstream>
#include <iostream>
#include <set>
#include <tuple>
#include <vector>

enum directionection {
	UP, 
	DOWN,
	LEFT,
	RIGHT
};

bool moveGuard(std::vector<std::string> &map, int x, int y, enum directionection direction, int startX, int startY) 
{
	std::set<std::tuple<int, int, directionection>> visited; // To track visited positions and directions

	while (true)
	{
		if (x < 0 || x >= map.size() || y < 0 || y >= map[0].size())
			return false;

		if (visited.count({x, y, direction}))
		{
			/*std::cout << "x, y, direction: " << x << ", " << y << ", " << direction <<std::endl;*/
			/*for (int i = 0; i < map.size(); i++)*/
			/*{*/
			/*	std::cout << map[i] << std::endl;*/
			/*}*/
			return true;
		}

		visited.insert({x, y, direction});

		map[x][y] = 'X';

		switch (direction) 
		{
		case UP:
			if (x - 1 >= 0)
				direction = map[x - 1][y] == '#' ? RIGHT : UP;
			if (direction == UP)
				x = x - 1;
			break;
		case DOWN:
			if (x + 1 < map.size())
				direction = map[x + 1][y] == '#' ? LEFT : DOWN;
			if (direction == DOWN)
				x = x + 1;
			break;
		case LEFT:
			if (y - 1 >= 0)
				direction = map[x][y - 1] == '#' ? UP : LEFT;
			if (direction == LEFT)
				y = y - 1;
			break;
		case RIGHT:
			if (y + 1 < map[0].size())
				direction = map[x][y + 1] == '#' ? DOWN : RIGHT;
			if (direction == RIGHT)
				y = y + 1;
			break;
		default:
			return (false);
			std::cout << "x, y: " << x << ", " << y << std::endl;
		}
	}
}

int countObstacleInsertions(std::vector<std::string> &map, int startX, int startY) 
{
	int count = 0;

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] != '#' && map[i][j] != '^')
			{
				std::vector<std::string> mapCopy = map;
				mapCopy[i][j] = '#';

				if (moveGuard(mapCopy, startX, startY, UP, startX, startY))
				{
					count++;
				}
				//std::cout << "x, y: " << i << ", " << j << std::endl;
			}
		}
	}

	return count;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide valid args" << std::endl;
		return (0);
	}

	std::fstream inputFile(av[1]);
	std::string line;
	std::vector<std::string> map;

	int guard_x = 0;
	int guard_y;
	bool	foundGuard = false;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;
		map.push_back(line);
		if (line.find_first_of('^') != -1)
		{
			foundGuard = true;
			guard_y = line.find_first_of('^');
		}
		if (!foundGuard)
			guard_x++;
	}

	std::cout << "start: " << guard_x << ", " << guard_y << std::endl;

	int count = countObstacleInsertions(map, guard_x, guard_y);

	std::cout << count << std::endl;

	return (0);
}

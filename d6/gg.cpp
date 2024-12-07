#include <fstream>
#include <iostream>
#include <vector>

enum direction {
	UP, 
	DOWN,
	LEFT,
	RIGHT
};

void	moveGuard(std::vector<std::string> &map, int x, int y, enum direction direction)
{	
	if (x >= map.size() || y >= map[0].size())
		return;
	map[x].replace(y, 1, 1, 'X');	
	switch (direction)
	{
	case (UP):
		if (x - 1 >= 0)
			direction = map[x - 1][y] == '#' ? RIGHT : UP;
		if (direction == UP)
			x = x - 1;
		break;
	case (DOWN):
		if (x + 1 < map.size())
			direction = map[x + 1][y] == '#' ? LEFT : DOWN;
		if (direction == DOWN)
			x = x + 1;
		break;
	case (LEFT):
		if (y - 1 >= 0)
			direction = map[x][y - 1] == '#' ? UP : LEFT;
		if (direction == LEFT)
			y = y - 1;
		break;
	case (RIGHT):
		if (y + 1 < map[0].size())
			direction = map[x][y + 1] == '#' ? DOWN : RIGHT;
		if (direction == RIGHT)
			y = y + 1;
		break;
	default:
		return;
	}
	moveGuard(map, x, y, direction);
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
	moveGuard(map, guard_x, guard_y, UP);

	int	count = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'X')
				count++;
		}
	}
	std::cout << count << std::endl;

	return (0);
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int	findPaths(std::vector<std::string> &map, int i, int j, int curr, int iter)
{
	if (iter > 10)
		return (0);
	if (i < 0 || j < 0 || i >= map.size() || j >= map[0].size())
		return (0);
	if (curr != map[i][j])
		return (0);
	if (curr == '9')
	{
		if (map[i][j] == '9')
		{
			return (1);
		}
		return (0);
	}

	int directions[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };	
	int sum = 0;

	for (int k = 0; k < 4; k++)
	{
		int*	dir = directions[k];
		int new_i = i + dir[0];
		int new_j = j + dir[1];
		sum += findPaths(map, new_i, new_j, curr + 1, iter + 1);
	}
	return (sum);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream fileInput(av[1]);
	std::string	line;
	std::vector<std::string> map;

	while (std::getline(fileInput, line))
	{
		if (line.empty())
			continue;
		map.push_back(line);
	}

	int sum = 0;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == '0')
			{
				std::vector<std::string> mapCopy = map;
				sum += findPaths(mapCopy, i, j, map[i][j], 1);
			}
		}
	}
	std::cout << sum << std::endl;

	return (0);
}

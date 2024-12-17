#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

std::pair<int, int>	moveDir(char c, int currX, int currY)
{
	switch (c)
	{
	case '^':
		return {currX, currY - 1};
	case '>':
		return {currX + 1, currY};
	case '<':
		return {currX - 1, currY};
	case 'v':
		return {currX, currY + 1};
	default:	
		return {-1, -1};
	}
}

std::pair<int, int>	push(std::vector<std::string> &map, std::pair<int, int> curr, char c)
{
	std::pair<int, int> next;
	std::pair<int, int>	currCopy = curr;
	while (true)
	{
		next = moveDir(c, curr.first, curr.second);
		char	currTile = map[next.second][next.first];
		if (currTile == '.')
		{
			map[next.second][next.first] = 'O';
			map[currCopy.second][currCopy.first] = '@';
			break ;
		}
		else if (currTile == '#')
		{
			break ;
		}
		curr = next;
	}
	return curr;
}

void	move(std::vector<std::string> &map, std::vector<std::string> moves, int startX, int startY)
{
	for (int i = 0; i < moves.size(); i++)
	{
		for (int j = 0; j < moves[i].size(); j++)
		{
			char	c = moves[i][j];
			std::pair<int, int> next = moveDir(c, startX, startY);
			char	nextTile = map[next.second][next.first];
			if (nextTile == 'O')
			{
				push(map, next, c);
				if (map[next.second][next.first] == '@')
				{
					map[startY][startX] = '.';
					startX = next.first;
					startY = next.second;
				}
			}
			else if (nextTile == '.')
			{
				map[startY][startX] = '.';
				map[next.second][next.first] = '@';
				startX = next.first;
				startY = next.second;
			}
		}
	}

}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		return (0);
	}

	std::fstream	input(av[1]);
	std::string	line;
	std::vector<std::string>	map;

	while (std::getline(input, line))
	{
		if (line.empty())
			break;
		map.push_back(line);
	}

	std::vector<std::string> moves;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		moves.push_back(line);
		std::cout << line << std::endl;
	}


	int	startX, startY;
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if (map[i][j] == '@')
			{
				startX = j;
				startY = i;
				break ;
			}
		}
	}

	move(map, moves, startX, startY);

	for (std::string s : map)
	{
		std::cout << s << std::endl;
	}

	unsigned long long res = 0;
	for (int i = 0; i< map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] == 'O')
			{
				res += i * 100 + j;
			}
		}
	}

	std::cout << res << std::endl;
	return (0);
}

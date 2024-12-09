#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::pair<int, int> getVector(std::pair<int, int> oa, std::pair<int, int> ob)
{
	int	dx = oa.first - ob.first;
	int	dy = oa.second - ob.second;
	return {dx, dy};
}

void	storeAntennas(std::multimap<int, std::pair<int, int> > &mMap, const std::vector<std::string> &map)
{
	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[i].size(); j++)
		{
			if (map[i][j] != '.')
			{
				mMap.insert({map[i][j], {i, j}});
			}
		}
	}
}

int	helper(std::vector<std::string> &map, std::pair<int, int> p1, std::pair<int, int> p2)
{
	std::pair<int, int> vector = getVector(p1, p2);	
	std::pair<int, int> v1 = {p1.first + vector.first, p1.second + vector.second};
	std::pair<int, int> v2 = {p2.first - vector.first, p2.second - vector.second};
	std::cout << "vector: (" << vector.first << ", "<<vector.second << ")" << std::endl;


	int	sum = 0;

	if (!(v1.first < 0 || v1.second < 0 || v1.first >= map.size() || v1.second >= map[0].size() || map[v1.first][v1.second] == '#'))
	{
		std::cout << "insert: (" << v1.first << ", " << v1.second<<")"<< std::endl;
		sum++;
		map[v1.first][v1.second] = '#';
	}
	if (!(v2.first < 0 || v2.second < 0 || v2.first >= map.size() || v2.second >= map[0].size() || map[v2.first][v2.second] == '#'))
	{
		std::cout << "insert: (" << v2.first << ", " << v2.second<<")"<< std::endl;
		sum++;
		map[v2.first][v2.second] = '#';
	}
	return (sum);
}

int	countAntinodes(std::vector<std::string> &map, std::vector<std::pair<int, int>> coords)
{
	int	sum = 0;
	if (coords.size() <= 1)
		return 0;
	for (int i = 0; i < coords.size(); i++)
	{
		for (int j = i + 1; j < coords.size(); j++)
		{
			std::cout << "("<< coords[i].first<<", " << coords[i].second << ") ("<< coords[j].first << ", "<< coords[j].second <<")"<< std::endl;
			sum += helper(map, coords[i], coords[j]);
		}
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

	std::fstream	inputFile(av[1]);
	std::string	line;

	std::vector<std::string>	map;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;
		map.push_back(line);
	}

	std::multimap<int, std::pair<int, int> > mMap;

	storeAntennas(mMap, map);

	std::multimap<int, std::pair<int, int>>::iterator itr;
	int	sum = 0;
	for (itr = mMap.begin(); itr != mMap.end(); itr++)
	{
		int	curr = itr->first;
		std::vector<std::pair<int, int>> coords;
		while (curr == itr->first)
		{
			coords.push_back(itr->second);
			itr++;
		}
		std::cout << "==================================\n" << (char)curr << std::endl;
		sum += countAntinodes(map, coords);
		std::cout << "==================================\n";
		itr--;
	}
	std::cout << sum << std::endl;

	return (0);
}

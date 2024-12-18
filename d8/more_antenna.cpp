#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

bool within_bound(std::pair<int, int>& pair, std::set<std::pair<int, int>>& unique_antinodes, int nrows, int ncols, int dx, int dy)
{
    int newX = pair.first + dx;
    int newY = pair.second + dy;

    std::pair<int, int> antinode = std::make_pair(newX, newY);

    if (newX >= 0 && newX < nrows && newY >= 0 && newY < ncols)
	{
        unique_antinodes.insert(antinode);
        return (true);
    }
    return (false);
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return (0);
	}

	std::fstream	input(av[1]);
	std::string	line;
    std::unordered_map<char, std::vector<std::pair<int, int>>> antennas;
	int	lineNumber = 0;
	int	len;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		len = line.size();
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] != '.')
				antennas[line[i]].push_back(std::make_pair(lineNumber, i));
		}
		lineNumber++;
	}

	int	width = lineNumber;
	std::set<std::pair<int, int>> uniqueAntinodes;
	int	sum = 0;

	for (auto item : antennas)
	{
		std::vector<std::pair<int, int>> list = item.second;
		for (int i = 0; i < list.size(); i++)
		{
			for (int j = i + 1; j < list.size(); j++)
			{
				int dy = list[i].second - list[j].second;
				int	dx = list[i].first - list[j].first;
				bool	v1 = true;
				bool	v2 = true;

				for (int k = 0; v1 || v2; k++)
				{
					v1 = within_bound(list[i], uniqueAntinodes, width, len, dx * k, dy * k);
					v2 = within_bound(list[i], uniqueAntinodes, width, len, -dx * k, -dy * k);
				}
			}
		}
		sum += list.size();
	}

	for (auto item : uniqueAntinodes)
	{
		bool	f = false;
		for (auto antenna : antennas)
		{
			for (int i = 0; i < antenna.second.size() && !f; i++)
			{
				if (antenna.second[i] == item)
				{
					f = true;
					sum--;
				}
			}
			if (f)
				break;
		}
	}

	std::cout << sum + uniqueAntinodes.size() << std::endl;

	return (0);
}

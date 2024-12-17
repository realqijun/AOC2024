#include <fstream>
#include <iostream>
#include <regex>
#include <string>

void	insertBot(int **map, std::string input)
{
	std::regex	pattern(R"((-?\d+))");
	std::sregex_iterator	it(input.begin(), input.end(), pattern);

	int startX = std::stoi(it++->str());
	int	startY = std::stoi(it++->str());
	int vectorX = std::stoi(it++->str());
	int vectorY = std::stoi(it->str());

	std::cout << startY << ", " << startX << " " << vectorX << ", " << vectorY << std::endl;

	int	endX = (startX + vectorX * 100) % 101;
	int	endY = (startY + vectorY * 100) % 103;
	if (endY < 0) endY += 103;
    if (endX < 0) endX += 101;

	std::cout << endY << ", " << endX << std::endl;
	map[endY][endX] += 1;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Wrong inputs" << std::endl;
		return (0);
	}

	std::fstream	input(av[1]);
	std::string	line;
	int	**map = new int*[103];	
	for (int i = 0; i < 103; i++)
		map[i] = new int[101]();

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		insertBot(map, line);
	}

	long long quadrant1 = 0;
	long long quadrant2 = 0;
	long long quadrant3 = 0;
	long long quadrant4 = 0;

	for (int i = 0; i < 103; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			if (map[i][j] != 0)
			{
				if (i < 51 && j < 50)
					quadrant1 += map[i][j];
				else if (i < 51 && j > 50)
					quadrant2 += map[i][j];
				else if (i > 51 && j < 50)
					quadrant3 += map[i][j];
				else if (i > 51 && j > 50)
					quadrant4 += map[i][j];
			}
		}
	}

	long long result = quadrant1 * quadrant2 * quadrant3 * quadrant4;
	std::cout << "Result: " << result << std::endl;

	for (int i = 0; i < 103; i++)
		delete[] map[i];
	delete[] map;
	return (0);
}

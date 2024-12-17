#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

struct Bot 
{
    int x, y;
    int vectorX, vectorY;
};

long long	countEntropy(int **map)
{
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
	return (result);
}

void	printMap(int **map)
{
	std::string red("\033[0;31m");
	std::string green("\033[0;32m");
	std::string reset("\033[0m");

	for (int i = 0; i < 103; i++)
	{
		for (int j = 0; j < 101; j++)
		{
			if (map[i][j] != 0)
				std::cout << red; 
			else
				std::cout << green; 
			std::cout << map[i][j];
		}
		std::cout << std::endl;
	}
}

void initializeBots(std::vector<Bot> &bots, std::string input)
{
    std::regex pattern(R"((-?\d+))");
    std::sregex_iterator it(input.begin(), input.end(), pattern);

    int startX = std::stoi(it++->str());
    int startY = std::stoi(it++->str());
    int vectorX = std::stoi(it++->str());
    int vectorY = std::stoi(it->str());

    bots.push_back({startX, startY, vectorX, vectorY});
}

void updateBotPosition(int **map, Bot &bot) 
{
    int prevX = bot.x % 101;
    int prevY = bot.y % 103;
    if (prevY < 0) prevY += 103;
    if (prevX < 0) prevX += 101;

    map[prevY][prevX] = 0;

    bot.x = (bot.x + bot.vectorX) % 101;
    bot.y = (bot.y + bot.vectorY) % 103;
    if (bot.y < 0) bot.y += 103;
    if (bot.x < 0) bot.x += 101;

    map[bot.y][bot.x] += 1;
}

void	clearAndReinit(int **map)
{
	for (int i = 0; i < 103; i++)
		delete[] map[i];
	delete[] map;
	map = new int*[103];	
	for (int i = 0; i < 103; i++)
		map[i] = new int[101](); 
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

    std::vector<Bot> bots;
	std::vector<Bot> botsCopy;
    while (std::getline(input, line)) 
	{
        if (line.empty())
            continue;
        initializeBots(bots, line);
    }
	botsCopy = bots;

	std::vector<long long>	safeties;

    for (int step = 0; step < 100; step++) 
	{
        for (Bot &bot : bots)
            updateBotPosition(map, bot);
		safeties.push_back(countEntropy(map));
    }

	std::sort(safeties.begin(), safeties.end());

	for (int i = 0; i < 5; i++) 
	{
		long long val = safeties[i];
		clearAndReinit(map);
		bots = botsCopy;
		for (int step = 0; step < 100; step++) 
		{
			std::cout << "debug" << std::endl;
			for (Bot &bot : bots)
				updateBotPosition(map, bot);
			if (countEntropy(map) == val)
				printMap(map);
		}
	}

	for (int i = 0; i < 103; i++)
		delete[] map[i];
	delete[] map;
	return (0);
}

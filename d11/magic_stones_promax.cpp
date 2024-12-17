#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

void	vectorize(std::unordered_map<unsigned long long, unsigned long long> &stones, std::string line)
{
	std::regex	pattern(R"((\d+))");
	std::sregex_iterator	it(line.begin(), line.end(), pattern);
	std::sregex_iterator	end;

	while (it != end)
	{
		unsigned long long stone = std::stoull(it->str());
		stones[stone] = 1;
		it++;
	}
}

void	stoneAlgo(std::unordered_map<unsigned long long, unsigned long long> &stones)
{
	for (int iter = 0; iter < 75; iter++)
	{
		std::unordered_map<unsigned long long, unsigned long long> updatedStones;
		for (auto pair : stones)
		{
			unsigned long long	key = pair.first;
			unsigned long long	val = pair.second;
			if (key == 0)
			{
				updatedStones[1] += val;
			}
			else if (std::to_string(key).length() % 2 == 0)
			{
				std::string	stone_string = std::to_string(key);
				unsigned long long stone = std::stoull(stone_string);
				unsigned long long base = pow(10, stone_string.length() / 2);
				updatedStones[stone / base] += val;
				updatedStones[stone % base] += val;
			}
			else
			{
				updatedStones[key * 2024] += val;
			}
		}
		stones = updatedStones;
	}
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
	std::getline(inputFile, line);

	std::unordered_map<unsigned long long, unsigned long long>	stones;
	vectorize(stones, line);
	stoneAlgo(stones);

	unsigned long long	sum = 0;
	std::unordered_map<unsigned long long, unsigned long long>::iterator	it = stones.begin();
	std::unordered_map<unsigned long long, unsigned long long>::iterator	end;
	while (it != end)
	{
		sum += it->second;
		it++;
	}
	std::cout << sum << std::endl;
	
	return (0);
}

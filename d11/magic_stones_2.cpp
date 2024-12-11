#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

void	vectorize(std::vector<std::string> &stones, std::string line)
{
	std::regex	pattern(R"((\d+))");
	std::sregex_iterator	it(line.begin(), line.end(), pattern);
	std::sregex_iterator	end;

	while (it != end)
	{
		std::string stone = it->str();
		stones.push_back(stone);
		it++;
	}
}

std::pair<std::string, std::string>	splitStones(std::string stone)
{
	size_t mid = stone.size() / 2;
	return {
		std::to_string(std::stol(stone.substr(0, mid))),
			std::to_string(std::stol(stone.substr(mid))) 
	};
}

void	stoneAlgo(std::vector<std::string> &stones)
{
	std::vector<std::string> updatedStones;

	for (int iter = 0; iter < 75; iter++)
	{
		for (int i = 0; i < stones.size(); i++)
		{
			std::string curr = stones[i];
			if (curr == "0")
			{
				updatedStones.push_back("1");
			}
			else if (curr.size() % 2 == 0)
			{
				std::pair<std::string, std::string> stone = splitStones(curr);
				updatedStones.push_back(stone.first);
				updatedStones.push_back(stone.second);
			}
			else
			{
				std::string newStone = std::to_string(std::stol(curr) * 2024);	
				updatedStones.push_back(newStone);
			}
		}
		stones = updatedStones;
		updatedStones.clear();
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

	std::vector<std::string>	stones;
	vectorize(stones, line);
	stoneAlgo(stones);

	std::cout << stones.size() << std::endl;
	return (0);
}

#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>
#include <unordered_set>

void	extractTowels(std::string line, std::unordered_set<std::string> &towels)
{
	std::regex	pattern(R"([a-zA-Z]+)");
	std::sregex_iterator	it(line.begin(), line.end(), pattern);
	std::sregex_iterator	end;

	while (it != end)
	{
		towels.insert(it->str());
		it++;
	}
}

int	make_towel(std::string input, std::unordered_set<std::string> towels, std::unordered_map<std::string, int> &memo)
{
    if (input.empty())
        return 1;

    if (memo.find(input) != memo.end())
        return memo[input];

	int	sum = 0;
	for (auto towel : towels)
	{
		if (input.find(towel) == 0) 
		{
			sum += make_towel(input.substr(towel.length()), towels, memo);
		}
	}

	memo[input] = sum;

	return (sum);
}

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (0);
	}

	std::string	line;
	std::unordered_set<std::string>	towels;

	std::getline(input, line);
	extractTowels(line, towels); 

	int	sum = 0;
	std::unordered_map<std::string, int> memo;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		sum += make_towel(line, towels, memo);
	}
	
	std::cout << sum << std::endl;
	return (0);
}

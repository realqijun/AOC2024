#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

bool checkTarget(const std::vector<long>& terms, int index, long currentValue, long target) 
{
	if (index == terms.size())
		return currentValue == target;

	return checkTarget(terms, index + 1, currentValue + terms[index], target) ||
		checkTarget(terms, index + 1, currentValue * terms[index], target);
}

long	valid(std::string line)
{
	std::regex	pattern(R"(\d+)");
	std::sregex_iterator	it(line.begin(), line.end(), pattern);
	std::sregex_iterator	end;

	long target = std::stol(it->str());
	it++;

	std::vector<long> terms;
	while (it != end) 
	{
		terms.push_back(std::stoi(it->str()));
		++it;
	}
	if (terms.empty())
		return 0;
	if (checkTarget(terms, 1, terms[0], target))
		return target;
	return (0);
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

	long	sum = 0;
	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;
		sum += valid(line);
	}

	std::cout << sum << std::endl;
	return (0);
}

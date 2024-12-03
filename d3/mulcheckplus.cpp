#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int	getSum(const std::string& input) 
{
    std::regex pattern(R"(mul\((\d+),(\d+)\)|do\(\)|don't\(\))");
    std::sregex_iterator it(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

	int	sum = 0;
	static bool	enable = true; // saves do/dont status between lines

    while (it != end)
	{
		std::cout << it->str() << enable << std::endl;
		if ((*it)[0].str() == "do()")
			enable = true;
		else if ((*it)[0].str() == "don't()")
			enable = false;
		else if (enable)
		{
			sum += std::stoi((*it)[1].str()) * std::stoi((*it)[2].str());
		}
		it++;
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

	std::fstream file(av[1]);
	std::string line;

	int sum = 0;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		sum += getSum(line);
		std::cout << std::endl;
	}
	
	std::cout << sum << std::endl;
	return (0);
}

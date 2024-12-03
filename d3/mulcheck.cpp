#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

std::vector<std::string> extractMulExpressions(const std::string& input) 
{
    std::regex pattern(R"(mul\((\d+),(\d+)\))");
    std::sregex_iterator it(input.begin(), input.end(), pattern);
    std::sregex_iterator end;
	std::vector<std::string> res;
    while (it != end)
	{
		    std::cout << "Full match: " << (*it)[0].str() << std::endl;
    std::cout << "Group 1: " << (*it)[1].str() << std::endl;
    std::cout << "Group 2: " << (*it)[2].str() << std::endl;
		res.push_back(it->str());
		it++;
	}
    return (res);
}

int getSop(const std::vector<std::string>& input) 
{
    int sum = 0;
    for (int i = 0; i < input.size(); i++) 
    {
		std::string expr = input.at(i);
        std::regex numberPattern("(\\d+)");
        std::sregex_iterator it(expr.begin(), expr.end(), numberPattern);
        std::sregex_iterator end;

        std::vector<int> numbers;
        while (it != end) 
        {
            numbers.push_back(std::stoi(it->str()));
            ++it;
        }
        if (numbers.size() == 2) 
            sum += numbers[0] * numbers[1];
    }
    return sum;
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
	std::vector<std::string> inputs;

	int sum = 0;
	while (std::getline(file, line))
	{
		if (line.empty())
			continue;
		inputs.push_back(line);
		std::vector<std::string> res = extractMulExpressions(line);
		sum += getSop(res);
	}
	
	std::cout << sum << std::endl;
	return (0);
}

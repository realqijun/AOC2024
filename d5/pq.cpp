#include <algorithm>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <utility>
#include <vector>

void	addRule(std::vector<std::pair<int, int>> &rules, std::string item)
{
	std::regex pattern(R"((\d+)\|(\d+))");
	std::sregex_iterator it(item.begin(), item.end(), pattern);
	if (it == std::sregex_iterator()) 
	{
		std::cout << "Invalid format: " << item << std::endl;
		return;
	}
	int first = std::stoi((*it)[1].str());
	int second = std::stoi((*it)[2].str());
	rules.emplace_back(first, second);
}

void	addPages(std::vector<int> &pages, std::string input)
{
	std::regex pattern(R"(\d+)");
	std::sregex_iterator it(input.begin(), input.end(), pattern);
	if (it == std::sregex_iterator())
	{
		std::cout << "Invalid format: " << input << std::endl;
		return;
	}
	std::sregex_iterator end;
	while (it != end) 
	{
		pages.push_back(std::stoi((*it).str()));
		++it;
	}
}

bool	isValidQueue(const std::vector<int> &pages, const std::vector<std::pair<int, int>> &rules)
{
	for (int i = 0; i < rules.size(); i++)
	{
		std::pair<int, int> curr = rules[i];
		auto firstIt = std::find(pages.begin(), pages.end(), curr.first);
		if (firstIt == pages.end())
		{
			while (i < rules.size() && rules[i].first == curr.first)
				i++;
		}
		else
		{
			auto secondIt = std::find(pages.begin(), pages.end(), curr.second);
			if (secondIt == pages.end())
				continue;
			else if (firstIt >= secondIt)
				return false;
		}
	}
	return (true);
}

int	getMidVal(const std::vector<int> &pages)
{
	int	mid = pages.size() / 2;
	return pages[mid];
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream inputFile(av[1]);
	std::string	line;
	std::vector<std::pair<int, int> > rules;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
			break ;
		addRule(rules, line);
	}

	int	sum = 0;
	while (std::getline(inputFile, line))
	{
		if (line.empty())
			break ;
		std::vector<int> pages;
		addPages(pages, line);
		if (isValidQueue(pages, rules))
			sum += getMidVal(pages);
	}

	std::cout << sum << std::endl;
	return (0);
}

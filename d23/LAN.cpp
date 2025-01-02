#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

void	insertPair(std::string line, std::set<std::pair<std::string, std::string>> &set)
{
	std::stringstream	ss(line);

	std::string	com1;
	std::string com2;

	std::getline(ss, com1, '-');
	std::getline(ss, com2, '-');
	std::getline(ss, com2, '-');

	if (com1 < com2)
	{
		set.insert({com1, com2});
	}
	else
	{
		set.insert({com2, com1});
	}
}

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::string	line;
	std::set<std::pair<std::string, std::string>>	set;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		insertPair(line, set); 
		break;
	}

	return (0);
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream	inputFile(av[1]);
	std::string	line;

	std::vector<std::string>	map;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;
		map.push_back(line);
	}

	return (0);
}

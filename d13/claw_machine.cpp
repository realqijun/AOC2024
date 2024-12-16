#include <fstream>
#include <iostream>
#include <string>

int	main(int ac, char ** av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream	inputFile(av[1]);
	std::string	line;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;

	}

	return (0);
}

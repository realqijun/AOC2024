#include <fstream>
#include <iostream>
#include <string>
#include <utility>

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (0);
	}

	std::string	line;
	int	lineNumber = 0;
	
	std::pair<int, int>	start;
	std::pair<int, int> end;

	while (std::getline(input, line))
	{
		if (line.empty())
			break;
		for (int i = 0; i < line.size(); i++)
		{
			if (line[i] == 'S')
				start = { lineNumber, i };
			if (line[i] == 'E')
				end = { lineNumber, i };
		}
		lineNumber++;
	}

	return (0);
}

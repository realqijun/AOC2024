#include <fstream>
#include <iostream>
#include <string>

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::string	line;
}

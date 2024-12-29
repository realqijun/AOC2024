#include <fstream>
#include <iostream>
#include <string>

unsigned long long	prune(unsigned long long secret)
{
	return secret % 16777216;
}

unsigned long long	first(unsigned long long secret)
{
	unsigned long long res = secret << 6;
	res ^= secret;
	return (prune(res));
}

unsigned long long	second(unsigned long long secret)
{
	unsigned long long res = secret >> 5;
	res ^= secret;
	return (prune(res));
}

unsigned long long	third(unsigned long long secret)
{
	unsigned long long res = secret << 11;
	res ^= secret;
	return (prune(res));
}

unsigned long long	get2000secret(unsigned long long secret)
{
	unsigned long long temp = secret;
	for (int i = 1; i <= 2000; i++)
	{
		temp = third(second(first(temp)));
	}
	return (temp);
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
	unsigned long long	sum;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		sum += get2000secret(std::stoull(line));
	}
	
	std::cout << sum << std::endl;

	return (0);
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void	print(std::vector<int> disk)
{
	for (int num : disk)
	{
		std::cout << num;
	}
	std::cout << std::endl;
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream inputFile(av[1]);
	std::string line;
	
	std::getline(inputFile, line);

	std::vector<int> disk;

	for (int i = 0; i < line.size(); i++)
	{
		int	val = line.at(i) - '0';
		int	thing = i % 2 == 0 ? (i / 2) : -1;
		while (val > 0)
		{
			disk.push_back(thing);
			val--;
		}
	}
	
    auto start_it = std::find_if(disk.begin(), disk.end(), [](int num) { return num == -1; });

    // Find the last non -1 from the end
    auto last_it = std::find_if(disk.rbegin(), disk.rend(), [](int num) { return num != -1; });

	while (start_it != disk.end() && last_it != disk.rend() && start_it < last_it.base() - 1)
    {
        std::iter_swap(start_it, last_it.base() - 1);

        start_it = std::find_if(start_it + 1, disk.end(), [](int num) { return num == -1; });

        last_it = std::find_if(last_it + 1, disk.rend(), [](int num) { return num != -1; });

    }

	print(disk);
	long sum = 0;
    for (int i = 0; i < disk.size(); i++)
    {
		if (disk.at(i) == -1)
			break;
        sum += i * disk.at(i);
    }
    std::cout << sum << std::endl;	
	return (0);
}

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
int getXmas(std::vector<std::string> grid)
{
    int sum = 0;
    int directions[8][2] = {
        {1, 0}, {-1, 0}, 
        {0, 1}, {0, -1},
        {1, 1}, {-1, -1},
        {-1, 1}, {1, -1} 
    };

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 'X')
            {
				std::cout << "at (i, j):" << "(" << i << ", " << j << ")" << std::endl;
                for (int k = 0; k < 8; k++)
                {
					int *dir = directions[k];
                    int l;
                    int x = i, y = j;
                    std::string word = "";
					std::cout << dir[0] << dir[1] << std::endl << x << y << std::endl;
                    for (l = 0; l < 4; l++)
                    {
                        if (x >= 0 && x < grid.size() && y >= 0 && y < grid[i].size())
                            word += grid[x][y];
                        else
                            break; // Out of bounds
                        x += dir[0]; // Move in the direction
                        y += dir[1];
                    }
					std::cout << word << std::endl;
                    if (l == 4 && word == "XMAS") // If the word is formed
					{
						std::cout << "spells XMAS\n" << std::endl;
                        sum++;
					}
                }
            }
        }
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

	std::fstream inputFile(av[1]);
	std::string	line;
	std::vector<std::string> grid;

	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;
		grid.push_back(line);	
	}
	
	int	sum = getXmas(grid);

	std::cout << sum << std::endl;
	return (0);
}

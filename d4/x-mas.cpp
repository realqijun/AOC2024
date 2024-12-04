#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int getXmas(std::vector<std::string> grid)
{
    int sum = 0;
    int directions[4][2] = {
        {1, 1}, {-1, -1},
        {-1, 1}, {1, -1} 
    };

    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[i].size(); j++)
        {
            if (grid[i][j] == 'A')
            {
				std::cout << "at (i, j):" << "(" << i << ", " << j << ")" << std::endl;

				int sCount = 0;
				int mCount = 0;

                for (int k = 0; k < 4; k++)
                {
					int *dir = directions[k];
                    int x = i, y = j;
					std::cout << dir[0] << dir[1] << std::endl << x << y << std::endl;
					x += dir[0]; // Move in the direction
					y += dir[1];
                    if (x >= 0 && x < grid.size() && y >= 0 && y < grid[i].size())
                    {
						if (grid[x][y] == 'S')
							sCount++;
						else if (grid[x][y] == 'M')
							mCount++;
						else
							break;
					}
                    else
						break; 
                }

				if (sCount == 2 && mCount == 2)
				{
					if (grid[i + directions[0][0]][j + directions[0][1]] == grid[i + directions[1][0]][j + directions[1][1]] || grid[i + directions[2][0]][j + directions[2][1]] == grid[i + directions[3][0]][j + directions[3][1]])
						;
					else
						sum++;
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

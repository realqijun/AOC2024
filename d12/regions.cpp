#include <fstream>
#include <iostream>
#include <queue>
#include <string>
#include <vector>

struct Region 
{
    char character;
	std::vector<std::pair<int, int>> coordinates;
	int perimeter;
};

void bfs(const std::vector<std::string>& map, std::vector<std::vector<bool>>& visited, int startRow, int startCol, Region& region)
{
	int	rows = map.size();
	int	cols = map[0].size();
	char	toFind = map[startRow][startCol];

	std::queue<std::pair<int, int>>	q;
	q.push({startRow, startCol});
	visited[startRow][startCol] = true;

	int	directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	while (!q.empty())
	{
		std::pair<int, int> curr = q.front();
		q.pop();
		region.coordinates.push_back(curr);

		for (int k = 0; k < 4; k++)
		{
			int	*dir = directions[k];
			int nextRow = curr.first + dir[0];
			int	nextCol = curr.second + dir[1];

			if (nextRow < 0 || nextCol < 0 || nextRow >= rows || nextCol >= cols) 
                region.perimeter++;
			else if (map[nextRow][nextCol] != region.character)
                region.perimeter++;
			else if (nextRow >= 0 && nextRow < rows && nextCol >= 0 && nextCol < cols && !visited[nextRow][nextCol] && map[nextRow][nextCol] == toFind) 
			{
				visited[nextRow][nextCol] = true;
				q.push({nextRow, nextCol});
			}
		}
		
	}
}

void	bfsInsert(std::vector<std::string> &map, std::vector<Region> &regions)
{
	int rows = map.size();
    int cols = map[0].size();
	std::vector<std::vector<bool>> visited(rows, std::vector<bool>(cols, false));

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (!visited[i][j])
			{
				Region region;
				region.character = map[i][j];
				region.perimeter = 0;
				bfs(map, visited, i, j, region);
				regions.push_back(region);
			}
		}
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream	input(av[1]);
	std::string	line;
	std::vector<std::string>	map;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		map.push_back(line);
	}
	
	std::vector<Region> regions;
	bfsInsert(map, regions);

	int	sum = 0;
	for (Region r : regions)
	{
		sum += r.perimeter * r.coordinates.size();
	}
	std::cout << sum << std::endl;

	/*for (Region r : regions)
	{
		std::cout << r.character << ": ";
		std::vector<std::pair<int, int>> coords = r.coordinates;
		for (std::pair<int, int> coord : coords)
		{
			std::cout << "(" << coord.first << ", " << coord.second << ")";
		}
		std::cout << std::endl << "perimeter: " << r.perimeter << std::endl;
	}
	*/

	return (0);
}

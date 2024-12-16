#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <vector>

struct Region 
{
    char character;
	std::vector<std::pair<int, int>> coordinates;
	int perimeter;
};

struct Edge 
{
    int startRow, startCol, endRow, endCol;
    bool operator<(const Edge& other) const {
        return std::tie(startRow, startCol, endRow, endCol) < std::tie(other.startRow, other.startCol, other.endRow, other.endCol);
    }
};

void bfs(const std::vector<std::string>& map, std::vector<std::vector<bool>>& visited, int startRow, int startCol, char regionChar, std::set<Edge> &edges)
{
	int	rows = map.size();
	int	cols = map[0].size();

	std::queue<std::pair<int, int>>	q;
	q.push({startRow, startCol});
	visited[startRow][startCol] = true;

	int	directions[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

	while (!q.empty())
	{
		std::pair<int, int> curr = q.front();
		q.pop();
		int cellSides = 4;

		for (int k = 0; k < 4; k++)
		{
			int	*dir = directions[k];
			int nextRow = curr.first + dir[0];
			int	nextCol = curr.second + dir[1];

            if (nextRow < 0 || nextRow >= rows || nextCol < 0 || nextCol >= cols || map[nextRow][nextCol] != regionChar) {
                // Add boundary edge
                if (dir[0] == 0) { // Horizontal edge
                    edges.insert({curr.first, curr.second, curr.first, curr.second + 1});
                } else { // Vertical edge
                    edges.insert({curr.first, curr.second, curr.first + 1, curr.second});
                }
                continue;
            }
			if (!visited[nextRow][nextCol])
			{
				visited[nextRow][nextCol] = true;
				q.push({nextRow, nextCol});
			}
		}
		
	}
}

void	bfsInsert(std::vector<std::string> &map, std::vector<std::pair<char, int>> &regions)
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
				char	regionChar = map[i][j];
				std::set<Edge> edge;
				bfs(map, visited, i, j, regionChar, edge);
				regions.push_back({regionChar, edge.size()});
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
	
	std::vector<std::pair<char, int>> regions;
	bfsInsert(map, regions);

	for (const auto& [regionChar, perimeter] : regions) {
		std::cout << "Region '" << regionChar << "' - Perimeter: " << perimeter << std::endl;
    }

	return (0);
}

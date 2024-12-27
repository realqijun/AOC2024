#include <climits>
#include <fstream>
#include <iostream>
#include <queue>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

enum DIRECTION {
    NORTH,
    SOUTH,
    EAST,
    WEST
};

int bfs(std::vector<std::string> &map, std::pair<int, int> start, std::pair<int, int> end) 
{
    std::set<std::tuple<std::pair<int, int>, DIRECTION>> visited;
    std::priority_queue<std::tuple<int, std::pair<int, int>, DIRECTION>, 
                        std::vector<std::tuple<int, std::pair<int, int>, DIRECTION>>,
                        std::greater<>> pq; // Min-heap for shortest path

    int directions[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
    pq.push({0, start, EAST});

    while (!pq.empty()) 
	{
        auto [cost, coord, dir] = pq.top();
        pq.pop();

        if (visited.count({coord, dir}))
            continue;

        visited.insert({coord, dir});

        if (coord == end)
            return cost;

        std::pair<int, int> newCoord = {coord.first + directions[dir][0], coord.second + directions[dir][1]};

        if (newCoord.first >= 0 && newCoord.first < map.size() &&
            newCoord.second >= 0 && newCoord.second < map[0].size() &&
            map[newCoord.first][newCoord.second] != '#' &&
            !visited.count({newCoord, dir}))
		{
            pq.push({cost + 1, newCoord, dir});
        }

        for (int turn : {-1, 1}) 
		{
            DIRECTION newDir = static_cast<DIRECTION>((dir + turn + 4) % 4);
            if (!visited.count({coord, newDir}))
                pq.push({cost + 1000, coord, newDir});
        }
    }

    return -1;
}

int main(int ac, char **av)
{
    if (ac != 2) 
	{
        std::cout << "Error" << std::endl;
        return (0);
    }

    std::ifstream input(av[1]);
    std::string line;
    int lineNumber = 0;

    std::pair<int, int> start;
    std::pair<int, int> end;
    std::vector<std::string> map;

    while (std::getline(input, line)) 
	{
        if (line.empty())
            continue;
        map.push_back(line);
        for (int i = 0; i < line.size(); i++) 
		{
            if (line[i] == 'S')
                start = {lineNumber, i};
            else if (line[i] == 'E')
                end = {lineNumber, i};
        }
        lineNumber++;
    }

    int result = bfs(map, start, end);
    if (result != -1)
        std::cout << "Shortest path cost: " << result << std::endl;
    else
        std::cout << "No path found." << std::endl;
    return (0);
}


#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void	printVector(std::vector<int> levels)
{
	for (int i = 0; i < levels.size(); i++)
	{
		std::cout << levels.at(i);
		if (i < levels.size() - 1)
			std::cout << " ";
	}
	std::cout << std::endl;
}

bool	stable(const std::vector<int>& levels) {
    if (levels.size() < 2) 
		return false;

    int curr = levels.at(0);
    bool increasing = levels.at(1) > curr;
    for (size_t i = 1; i < levels.size(); ++i) {
        int next = levels.at(i);
        if (std::abs(next - curr) > 3 || next == curr || (increasing && next < curr) || (!increasing && next > curr)) {
			return (false);
        }
        curr = next;
    }
    return (true);
}

bool countStableAfterRemoval(const std::vector<int>& levels)
{
    for (size_t i = 0; i < levels.size(); ++i)
	{
        std::vector<int> modifiedLevels = levels;
        modifiedLevels.erase(modifiedLevels.begin() + i); 
        if (stable(modifiedLevels))
			return (true);
    }
    return (false);
}

std::vector<int>	vectorize(std::string input)
{
	std::vector<int> ret;
	std::stringstream ss(input);
	std::string word;

    while (ss >> word) { // Read each number as a string
        try {
            ret.push_back(std::stoi(word)); // Convert to int and push to vector
        } catch (const std::invalid_argument&) {
            std::cerr << "Invalid data: " << word << " - Skipping line." << std::endl;
            ret.clear(); // Clear the vector to indicate a parsing error
            break;
        }
    }
	return (ret);
}

int	main(int ac, char **av)
{
    if (ac != 2)
	{
        std::cerr << "Usage: " << av[0] << " <filename>" << std::endl;
        return (1);
    }

    std::fstream input(av[1]);
    if (!input.is_open()) 
	{
        std::cerr << "Error: Could not open file " << av[1] << std::endl;
        return (1);
    }

    std::string line;
    int stableCount = 0;
    while (std::getline(input, line)) 
	{
        if (line.empty()) 
			continue;
        std::vector<int> levels = vectorize(line);
        if (!levels.empty())
		{
			if (stable(levels)) 
				++stableCount;
			else if (countStableAfterRemoval(levels))
				++stableCount;
        }
    }

    std::cout << "Number of stable sequences: " << stableCount << std::endl;
    return 0;
}

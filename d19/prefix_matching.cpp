#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <unordered_set>

void	extractTowels(std::string line, std::unordered_set<std::string> &towels)
{
	std::regex	pattern(R"([a-zA-Z]+)");
	std::sregex_iterator	it(line.begin(), line.end(), pattern);
	std::sregex_iterator	end;

	while (it != end)
	{
		towels.insert(it->str());
		it++;
	}
}


bool make_towel(const std::string &input, const std::unordered_set<std::string> &towels) 
{
    std::vector<bool> dp(input.size() + 1, false);
    dp[0] = true;

    for (size_t i = 1; i <= input.size(); i++) 
	{
        for (const auto &towel : towels) 
		{
            size_t len = towel.size();
            if (i >= len && input.substr(i - len, len) == towel) 
			{
                dp[i] = dp[i] || dp[i - len];
            }
        }
    }

    return dp[input.size()];
}

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (0);
	}

	std::string	line;
	std::unordered_set<std::string>	towels;

	std::getline(input, line);
	extractTowels(line, towels); 

	int	sum = 0;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		if (make_towel(line, towels))
			sum++;
	}
	
	std::cout << sum << std::endl;
	return (0);
}

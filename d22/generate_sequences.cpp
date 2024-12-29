#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

struct TupleHash {
    size_t operator()(const std::tuple<int, int, int, int>& t) const {
        auto [a, b, c, d] = t;
        size_t hash = 17;
        hash = hash * 31 + std::hash<int>()(a);
        hash = hash * 31 + std::hash<int>()(b);
        hash = hash * 31 + std::hash<int>()(c);
        hash = hash * 31 + std::hash<int>()(d);
        return hash;
    }
};

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

std::vector<int> get2000secret(unsigned long long secret)
{
	unsigned long long temp = secret;
	std::vector<int>	prices;
	prices.reserve(2000);
	for (int i = 0; i < 2000; i++)
	{
		temp = third(second(first(temp)));
		prices.push_back(temp % 10);
	}
	return (prices);
}

std::vector<std::tuple<int, int, int, int>> make4Tuple(std::vector<int> &inputs)
{
	std::vector<std::tuple<int, int, int, int>> res;
	size_t	size = inputs.size();
	res.reserve(size - 4);
	for (int i = 1; i < inputs.size() - 3; i++)
	{
		res.emplace_back(inputs[i] - inputs[i - 1], inputs[i + 1] - inputs[i],
                         inputs[i + 2] - inputs[i + 1], inputs[i + 3] - inputs[i + 2]);
	}
	return (res);
}

void addToSet(std::unordered_set<std::tuple<int, int, int, int>, TupleHash>& changes,
              const std::vector<std::tuple<int, int, int, int>>& list) 
{
    changes.insert(list.begin(), list.end());
}

int getSeqPrice(const std::tuple<int, int, int, int>& change, const std::vector<int>& price,
                const std::vector<std::tuple<int, int, int, int>>& changes) 
{
    auto it = std::find(changes.begin(), changes.end(), change);
    if (it != changes.end()) 
	{
        size_t index = std::distance(changes.begin(), it);
        if (index + 4 < price.size()) 
		{
            return price[index + 4];
        }
    }
    return -1;
}

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

    std::string line;
    std::unordered_set<std::tuple<int, int, int, int>, TupleHash> changeSet;
    std::vector<std::vector<std::tuple<int, int, int, int>>> changes;
    std::vector<std::vector<int>> prices;

	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		std::vector<int>	price = get2000secret(std::stoull(line));
		std::vector<std::tuple<int, int, int, int>>	change = make4Tuple(price);
		addToSet(changeSet, change); 
		changes.push_back(std::move(change));
		prices.push_back(std::move(price));
	}

	int max = INT_MIN;
	for (auto &item : changeSet)
	{
		int temp = 0;
		for (int i = 0; i < prices.size(); i++)
		{
			int ans = getSeqPrice(item, prices[i], changes[i]);
			if (ans != -1)
				temp += ans;
		}
		if (temp > max)
			max = temp;
	}
	
	std::cout << max << std::endl;

	return (0);
}

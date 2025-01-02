#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

void	insert(std::unordered_map<std::string, bool> &map, std::string tgt, bool newVal)
{
	if (map.count(tgt) == 0)
	{
		map.insert({tgt, newVal});
	}
	else
	{
		bool	&val = map.at(tgt);
		val = newVal;
	}
}


void	do_op(std::unordered_map<std::string, bool> &map, std::string lit1, std::string lit2, std::string tgt, std::string op)
{
	int val1 = map.at(lit1);
	int	val2 = map.at(lit2);

	if (op == "OR")
	{
		insert(map, tgt, val1 | val2);
	}
	else if (op == "XOR")
	{
		insert(map, tgt, val1 ^ val2);
	}
	else if (op == "AND")
	{
		insert(map, tgt, val1 & val2);
	}
	else
	{
		std::cerr << "Error" << std::endl;
		return ;
	}
}

int	main(void)
{
	std::ifstream	input("input.txt");

	if (!input.is_open())
	{
		std::cerr << "Error" << std::endl;
		return (1);
	}

	std::unordered_map<std::string, bool>	map;
	std::string	line;
	
	std::regex	pattern(R"((\d+))");
	while (std::getline(input, line))
	{
		if (line.empty())
			break;
		std::stringstream	ss(line);
		std::string key;
		std::getline(ss, key, ':');

		std::sregex_iterator	it(line.begin(), line.end(), pattern);
		int	val = std::stoi((++it)->str());

		map.insert({key, val});
	}

	std::queue<std::string> ops;
	std::unordered_map<std::string, bool>::iterator	end;

	std::regex	s_pattern(R"([a-zA-Z]+)");
	while (std::getline(input, line))
	{
		if (line.empty())
			continue;
		std::stringstream	ss(line);
		std::string	lit1, lit2, op, tgt;

		std::getline(ss, lit1, ' ');
		std::getline(ss, op, ' ');
		std::getline(ss, lit2, ' ');

		if (map.find(lit1) == end || map.find(lit2) == end)
		{
			ops.push(line);
		}
		else
		{
			std::getline(ss, tgt, ' ');
			std::getline(ss, tgt, ' ');
			do_op(map, lit1, lit2, tgt, op);
		}
	}

	while (!ops.empty())
	{
		std::string line = ops.front();
		ops.pop();

		std::stringstream	ss(line);
		std::string	lit1, lit2, op, tgt;

		std::getline(ss, lit1, ' ');
		std::getline(ss, op, ' ');
		std::getline(ss, lit2, ' ');

		if (map.find(lit1) == end || map.find(lit2) == end)
		{
			ops.push(line);
		}
		else
		{
			std::getline(ss, tgt, ' ');
			std::getline(ss, tgt, ' ');
			do_op(map, lit1, lit2, tgt, op);
		}
	}

	std::multimap<std::string, int> multi_map;
	for (auto &item : map)
	{
		if (item.first[0] == 'z')
		{
			multi_map.insert({item.first, item.second});
		}
	}

	uint64_t	res = 0;
	int mag = 0;
	for (auto &item : multi_map)
	{
		if (item.second)
		{
			res |= (unsigned long long)1 << mag;
		}
		mag++;
	}

	std::cout << res << std::endl;

	return (0);
}

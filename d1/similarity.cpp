#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

void	getInput(std::string s, std::vector<int> &col1, std::vector<int> &col2)
{
	std::stringstream ss(s);
	std::string word;
	getline(ss, word, ' ');
	col1.push_back(stoi(word));
	
	// skip spaces
	getline(ss, word, ' ');
	getline(ss, word, ' ');

	getline(ss, word, ' ');
	col2.push_back(stoi(word));
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the valid args" << std::endl;
		return (0);
	}

	std::fstream inputFile(av[1]);
	std::string line;
	std::vector<int> col1;
	std::vector<int> col2;
	while (getline(inputFile, line)) 
	{
		getInput(line, col1, col2);
	}
	inputFile.close();

	std::map<int, int> mapOfCol2;
	for (int i = 0; i < col2.size(); i++)
	{
		mapOfCol2[col2.at(i)]++;
	}

	int sum = 0;
	for (int i = 0; i< col1.size(); i++)
	{
		sum += mapOfCol2[col1.at(i)] * col1.at(i);
	}
	std::cout << sum << std::endl;

	return (0);
}

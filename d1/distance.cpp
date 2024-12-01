#include <cmath>
#include <fstream>
#include <iostream>
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

bool comp(int a, int b) {
    return (a < b);
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
		// std::cout << col1.back() << " " << col2.back() << "\n"; 
	}
	inputFile.close();

	std::sort(col1.begin(), col1.end(), comp);
	std::sort(col2.begin(), col2.end(), comp);

	std::vector<int> differences;
	for (int i = 0; i < col1.size(); i++)
	{
		differences.push_back(abs(col1.at(i) - col2.at(i))); // at is used over square brackets to provide error details
	}

	int sum = 0;
	/*for (int item : differences)
	{
		sum += item;
	}*/
	for (int i = 0; i < differences.size(); i++)
	{
		sum += differences.at(i);
	}

	std::cout << sum << std::endl;

	return (0);
}

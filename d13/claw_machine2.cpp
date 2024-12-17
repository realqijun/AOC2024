#include <fstream>
#include <iostream>
#include <regex>
#include <string>

std::vector<double> solve(double **matrix, double *exp) 
{
    double D = (matrix[0][0] * matrix[1][1]) - (matrix[1][0] * matrix[0][1]);
    double Dx = (exp[0] * matrix[1][1]) - (exp[1] * matrix[0][1]);
    double Dy = (matrix[0][0] * exp[1]) - (matrix[1][0] * exp[0]);
 
    double x = Dx / D;
    double y = Dy / D;

	std::cout << Dx << ", " << Dy << std::endl;
 
    return {x, y};
}

unsigned long long solve(std::vector<std::string> input)
{
	std::regex	pattern(R"((\d+))");

    double** matrix = new double*[2];

    for (int i = 0; i < 2; ++i) 
        matrix[i] = new double[2];

    for (int i = 0; i < 2; ++i) 
	{
        std::string row = input[i];
        std::sregex_iterator it(row.begin(), row.end(), pattern);
        std::sregex_iterator end;

        int col = 0;
        while (it != end && col < 2) 
		{
            matrix[i][col] = std::stod(it->str());
            ++it;
            ++col;
        }
    }

	double	temp = matrix[0][1];
	matrix[0][1] = matrix[1][0];
	matrix[1][0] = temp;

	double *exp = new double[2];	
	std::string row = input[2];
    std::sregex_iterator it(row.begin(), row.end(), pattern);
	exp[0] = std::stod(it->str()) + 10000000000000;
	exp[1] = std::stod((++it)->str()) + 10000000000000;
	
	std::vector<double> res = solve(matrix, exp);

	unsigned long long	sum = 0;
	if ((unsigned long long) res[0] == res[0] && (unsigned long long) res[1] == res[1]) 
        sum += (res[0] * 3) + (res[1] * 1);
	return (sum);
}

int	main(int ac, char ** av)
{
	if (ac != 2)
	{
		std::cout << "Please provide the correct args" << std::endl;
		return (0);
	}

	std::fstream	inputFile(av[1]);
	std::string	line;
	unsigned long long sum = 0;
	while (std::getline(inputFile, line))
	{
		if (line.empty())
			continue;
		std::vector<std::string> inputs;
		inputs.push_back(line);
		std::getline(inputFile, line);
		inputs.push_back(line);
		std::getline(inputFile, line);
		inputs.push_back(line);
		sum += solve(inputs);
	}
	std::cout << sum << std::endl;

	return (0);
}

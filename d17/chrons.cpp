#include <cmath>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

void	abcdv(int *toStore, int combo, int A)
{
	int	denom = std::pow(2, combo);
	*toStore = A / denom;
}

void	bxl(int *B, int lit)
{
	int	res = *B ^ lit;
	*B = res;
}

void	bst(int *B, int combo)
{
	*B = combo % 8;
}

bool	jnz(int A)
{
	return (A != 0);
}

void	bxc(int *B, int *C)
{
	int temp = *B ^ *C;
	*B = temp;
}

void	out(int combo)
{
	static int i = 0;

	if (i != 0)
		std::cout << ",";
	std::cout << combo % 8;
	i++;
}

int	getCombo(int index, int A, int B, int C)
{
	switch (index)
	{
	case 0:
		return (0);
	case 1:
		return (1);
	case 2:
		return (2);
	case 3:
		return (3);
	case 4:
		return (A);
	case 5:
		return (B);
	case 6:
		return (C);
	case 7:
		return (-1);
	default: 
		return (0);
	}
}

void	run(std::vector<int> program, int *A, int *B, int *C)
{
	size_t i = 0;
	int iters = 0;
	while (i < program.size())
	{
		int	op = program[i];
		int next = program[i + 1];
		switch (op)
		{
		case 0:
			abcdv(A, getCombo(next, *A, *B, *C), *A);
			break;
		case 1:
			bxl(B, next);
			break;
		case 2:
			bst(B, getCombo(next, *A, *B, *C));
			break;
		case 3:
			if (jnz(*A))
				i = next;
			else
				i+=2;
			continue;
		case 4:
			bxc(B, C);
			break;
		case 5:
			out(getCombo(next, *A, *B, *C));
			break;
		case 6:
			abcdv(B, getCombo(next, *A, *B, *C), *A);
			break;
		case 7:
			abcdv(C, getCombo(next, *A, *B, *C), *A);
			break;
		default:
			break ;
		}
		i += 2;
	}
}

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << "Error" << std::endl;
		return (0);
	}

	int	regA;
	int	regB;
	int	regC;

	std::fstream	input(av[1]);
	std::string	line;
	std::regex	pattern(R"((\d+))");
	
	std::getline(input, line);
	std::sregex_iterator	it(line.begin(), line.end(), pattern);
	regA = std::stol(it->str());

	std::getline(input, line);
	it = std::sregex_iterator(line.begin(), line.end(), pattern);
	regB = std::stol(it->str());

	std::getline(input, line);
	it = std::sregex_iterator(line.begin(), line.end(), pattern);
	regC = std::stol(it->str());

	std::getline(input, line);
	std::getline(input, line);
	std::vector<int>	program;
	it = std::sregex_iterator(line.begin(), line.end(), pattern);
	std::sregex_iterator	end;
	while (it != end)
	{
		program.push_back(std::stoi(it->str()));
		it++;
	}

	run(program, &regA, &regB, &regC);

	return (0);
}
